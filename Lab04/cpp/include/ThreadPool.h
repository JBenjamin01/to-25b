#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool {
public:
    // Nro especificado de hilos trabajadores
    ThreadPool(size_t threads);
    
    // Este destructor va a detener y unir todos los hilos
    ~ThreadPool();

    // Método para añadir una nueva tarea a la cola.
    // Tiene que dar un std::future con el que se puede obtener el valor de retorno de la tarea.
    template<class F, class... Args>
    auto encolar(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type>;

private:
    // Vector para guardar los hilos trabajadores.
    std::vector<std::thread> workers;
    
    // Cola de tareas, guarda cualquier función como lambdas, etc
    std::queue<std::function<void()>> tasks;

    // Mutex para proteger el acceso a la cola de tareas
    std::mutex queue_mutex;
    
    // Esta variable será para sincronizar los hilos
    std::condition_variable condition;
    
    // El fin de los hilos
    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    // Bloqueo único para proteger la sección crítica
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    
                    // El hilo espera aquí hasta que haya una tarea o se deba detener
                    this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    
                    if (this->stop && this->tasks.empty()) return;
                    
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

// Implementación de encolar()
template<class F, class... Args>
auto ThreadPool::encolar(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type> {
    using return_type = typename std::invoke_result<F, Args...>::type;

    // Tecnicamente se crea una tarea empaquetada que envuelve la función
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    
    // Obtiene el futuro que se asocia a esa tarea
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop) throw std::runtime_error("encolar en un ThreadPool detenido");
        tasks.emplace([task]() { (*task)(); });
    }
    // Se le avisa a un hilo en espera que hay una nueva tarea
    condition.notify_one();
    return res;
}

// Destructor
inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers) {
        worker.join();
    }
}

#endif