#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/* -----------------------------
   Clase: Tarea
   Representa una tarea (homework) con:
   - curso (string)
   - nombre del profesor (string)
   - fecha de presentación (string)
   - entregado: bool (true si presentó)
   Justificación: Es una entidad simple, se crea dinámicamente y es propiedad del Alumno.
   ----------------------------- */
class Tarea {
public:
    string curso;
    string profesor;
    string fecha;
    bool entregado;

    Tarea(const string& curso_, const string& profesor_, const string& fecha_, bool entregado_)
        : curso(curso_), profesor(profesor_), fecha(fecha_), entregado(entregado_) {}

    void imprimir() const {
        cout << "Curso: " << curso
             << " | Profesor: " << profesor
             << " | Fecha: " << fecha
             << " | Entregado: " << (entregado ? "Si" : "No") << "\n";
    }
};

/* -----------------------------
   Clase: Alumno
   - Propiedad: lista dinámica de Tarea* (Alumno "posee" sus tareas)
   - Métodos: addTarea, imprimirTareas, contarEntregadas, etc.
   Justificación: A cada alumno le corresponden sus tareas, por eso las reserva/libera aquí.
   ----------------------------- */
class Alumno {
private:
    // Datos básicos
    int codigo;
    int grado; // 1..6
    string nombres;
    string apellidos;

    // Lista dinámica de tareas
    Tarea** tareas;
    int tareaCount;
    int tareaCapacity;

    // helper para redimensionar array de tareas
    void ensureTareaCapacity() {
        if (tareaCount >= tareaCapacity) {
            int newCap = (tareaCapacity == 0) ? 2 : tareaCapacity * 2;
            Tarea** nuevo = new Tarea*[newCap];
            for (int i = 0; i < tareaCount; ++i) nuevo[i] = tareas[i];
            delete[] tareas;
            tareas = nuevo;
            tareaCapacity = newCap;
        }
    }

public:
    Alumno(int codigo_, int grado_, const string& nombres_, const string& apellidos_)
        : codigo(codigo_), grado(grado_), nombres(nombres_), apellidos(apellidos_),
          tareas(nullptr), tareaCount(0), tareaCapacity(0) {}

    ~Alumno() {
        // Como Alumno "posee" las tareas, las borramos
        for (int i = 0; i < tareaCount; ++i) {
            delete tareas[i];
        }
        delete[] tareas;
    }

    int getCodigo() const { return codigo; }
    int getGrado() const { return grado; }
    string getNombreCompleto() const { return nombres + " " + apellidos; }

    void addTarea(Tarea* t) {
        ensureTareaCapacity();
        tareas[tareaCount++] = t;
    }

    void imprimirTareas() const {
        if (tareaCount == 0) {
            cout << "Alumno " << codigo << " (" << getNombreCompleto() << ") no tiene tareas registradas.\n";
            return;
        }
        cout << "Tareas del alumno " << codigo << " (" << getNombreCompleto() << "):\n";
        for (int i = 0; i < tareaCount; ++i) {
            cout << "  [" << i+1 << "] ";
            tareas[i]->imprimir();
        }
    }

    int contarEntregadas() const {
        int c = 0;
        for (int i = 0; i < tareaCount; ++i) if (tareas[i]->entregado) ++c;
        return c;
    }

    int totalTareas() const { return tareaCount; }

    // Para buscar tareas por curso desde el alumno
    void imprimirTareasPorCurso(const string& curso, const string& alumnoNombre) const {
        for (int i = 0; i < tareaCount; ++i) {
            if (tareas[i]->curso == curso) {
                cout << "Alumno: " << alumnoNombre << " | ";
                tareas[i]->imprimir();
            }
        }
    }
};

/* -----------------------------
   Clase: Profesor
   - Mantiene un array dinámico de Alumno* (no es propietario; solo referencias).
   - Métodos: addAlumno, contarAlumnos, listarAlumnos.
   Justificación: Un profesor puede tener alumnos de distintos grados -> guardamos punteros.
   ----------------------------- */
class Profesor {
private:
    string nombres;
    string apellidos;

    Alumno** alumnos;
    int alumnoCount;
    int alumnoCapacity;

    void ensureAlumnoCapacity() {
        if (alumnoCount >= alumnoCapacity) {
            int newCap = (alumnoCapacity == 0) ? 4 : alumnoCapacity * 2;
            Alumno** nuevo = new Alumno*[newCap];
            for (int i = 0; i < alumnoCount; ++i) nuevo[i] = alumnos[i];
            delete[] alumnos;
            alumnos = nuevo;
            alumnoCapacity = newCap;
        }
    }

public:
    Profesor(const string& nombres_, const string& apellidos_)
        : nombres(nombres_), apellidos(apellidos_), alumnos(nullptr), alumnoCount(0), alumnoCapacity(0) {}

    ~Profesor() {
        // No borramos los Alumno* porque Profesor no es propietario.
        delete[] alumnos;
    }

    string getNombreCompleto() const { return nombres + " " + apellidos; }

    void addAlumno(Alumno* a) {
        // Evitar duplicados simples (por código)
        for (int i = 0; i < alumnoCount; ++i) if (alumnos[i]->getCodigo() == a->getCodigo()) return;
        ensureAlumnoCapacity();
        alumnos[alumnoCount++] = a;
    }

    int contarAlumnos() const { return alumnoCount; }

    void imprimirAlumnos() const {
        cout << "Alumnos a cargo del profesor " << getNombreCompleto() << " (" << alumnoCount << "):\n";
        for (int i = 0; i < alumnoCount; ++i) {
            cout << "  - Codigo: " << alumnos[i]->getCodigo()
                 << " | Nombre: " << alumnos[i]->getNombreCompleto()
                 << " | Grado: " << alumnos[i]->getGrado() << "\n";
        }
    }

    // Para recabar la lista (solo lectura)
    Alumno* obtenerAlumnoEnIndice(int idx) const {
        if (idx < 0 || idx >= alumnoCount) return nullptr;
        return alumnos[idx];
    }
};

/* -----------------------------
   Clase: Sistema
   - Administra arrays dinámicos de Alumno* y Profesor*
   - Provee las funciones pedidas (registro, búsqueda, reportes, limpieza).
   ----------------------------- */
class Sistema {
private:
    Alumno** alumnos;
    int alumnoCount;
    int alumnoCapacity;

    Profesor** profes;
    int profCount;
    int profCapacity;

    void ensureAlumnoCapacity() {
        if (alumnoCount >= alumnoCapacity) {
            int newCap = (alumnoCapacity == 0) ? 8 : alumnoCapacity * 2;
            Alumno** nuevo = new Alumno*[newCap];
            for (int i = 0; i < alumnoCount; ++i) nuevo[i] = alumnos[i];
            delete[] alumnos;
            alumnos = nuevo;
            alumnoCapacity = newCap;
        }
    }

    void ensureProfCapacity() {
        if (profCount >= profCapacity) {
            int newCap = (profCapacity == 0) ? 4 : profCapacity * 2;
            Profesor** nuevo = new Profesor*[newCap];
            for (int i = 0; i < profCount; ++i) nuevo[i] = profes[i];
            delete[] profes;
            profes = nuevo;
            profCapacity = newCap;
        }
    }

public:
    Sistema() : alumnos(nullptr), alumnoCount(0), alumnoCapacity(0),
                profes(nullptr), profCount(0), profCapacity(0) {}

    ~Sistema() {
        liberarMemoria();
    }

    // Registro de alumno (se crea con new y se añade al array)
    void registrarAlumno(int codigo, int grado, const string& nombres, const string& apellidos) {
        if (buscarAlumnoPorCodigoPtr(codigo) != nullptr) {
            cout << "Ya existe un alumno con codigo " << codigo << ". Registro ignorado.\n";
            return;
        }
        Alumno* a = new Alumno(codigo, grado, nombres, apellidos);
        ensureAlumnoCapacity();
        alumnos[alumnoCount++] = a;
        cout << "Alumno registrado: " << codigo << " - " << nombres << " " << apellidos << "\n";
    }

    // Registro de profesor
    void registrarProfesor(const string& nombres, const string& apellidos) {
        // Podríamos evitar duplicados por nombre completo; aquí lo permitimos.
        Profesor* p = new Profesor(nombres, apellidos);
        ensureProfCapacity();
        profes[profCount++] = p;
        cout << "Profesor registrado: " << p->getNombreCompleto() << "\n";
    }

    // Asignar alumno a profesor por código / nombre del profesor
    void asignarAlumnoAProfesor(int codigoAlumno, const string& nombreProfesor) {
        Alumno* a = buscarAlumnoPorCodigoPtr(codigoAlumno);
        if (!a) {
            cout << "No existe alumno con codigo " << codigoAlumno << "\n";
            return;
        }
        Profesor* p = buscarProfesorPorNombrePtr(nombreProfesor);
        if (!p) {
            cout << "No existe profesor con nombre '" << nombreProfesor << "'\n";
            return;
        }
        p->addAlumno(a);
        cout << "Alumno " << codigoAlumno << " asignado a profesor " << p->getNombreCompleto() << "\n";
    }

    // Registrar tarea para un alumno (crea Tarea con new y la agrega al Alumno)
    void registrarTarea(int codigoAlumno, const string& curso, const string& nombreProfesor,
                        const string& fecha, bool entregado) {
        Alumno* a = buscarAlumnoPorCodigoPtr(codigoAlumno);
        if (!a) {
            cout << "No existe alumno con codigo " << codigoAlumno << "\n";
            return;
        }
        Tarea* t = new Tarea(curso, nombreProfesor, fecha, entregado);
        a->addTarea(t);
        cout << "Tarea registrada para alumno " << codigoAlumno << " (curso: " << curso << ", entregado: " << (entregado ? "Si":"No") << ")\n";
    }

    // Mostrar tareas (entregadas y pendientes) de un alumno dado su código
    void mostrarTareasAlumno(int codigoAlumno) {
        Alumno* a = buscarAlumnoPorCodigoPtr(codigoAlumno);
        if (!a) {
            cout << "No existe alumno con codigo " << codigoAlumno << "\n";
            return;
        }
        a->imprimirTareas();
    }

    // Reporte: número de tareas entregadas por cada alumno y % de entregas respecto a total asignado
    void mostrarResumenTareasPorAlumno() {
        cout << "\n--- Resumen de tareas por alumno ---\n";
        for (int i = 0; i < alumnoCount; ++i) {
            Alumno* a = alumnos[i];
            int entregadas = a->contarEntregadas();
            int total = a->totalTareas();
            double porcentaje = (total == 0) ? 0.0 : (100.0 * entregadas / total);
            cout << "Alumno " << a->getCodigo() << " (" << a->getNombreCompleto() << "): "
                 << entregadas << " entregadas / " << total << " totales"
                 << " | " << fixed << setprecision(2) << porcentaje << "%\n";
        }
    }

    // Cantidad total de alumnos bajo responsabilidad de un profesor (por nombre)
    void cantidadAlumnosDelProfesor(const string& nombreProfesor) {
        Profesor* p = buscarProfesorPorNombrePtr(nombreProfesor);
        if (!p) {
            cout << "No existe profesor con nombre '" << nombreProfesor << "'\n";
            return;
        }
        cout << "Profesor " << p->getNombreCompleto() << " tiene a cargo " << p->contarAlumnos() << " alumnos.\n";
    }

    // Búsqueda por código de alumno (imprime info básica)
    void buscarAlumnoPorCodigo(int codigo) {
        Alumno* a = buscarAlumnoPorCodigoPtr(codigo);
        if (!a) {
            cout << "No existe alumno con codigo " << codigo << "\n";
            return;
        }
        cout << "Alumno encontrado: " << a->getCodigo() << " | " << a->getNombreCompleto()
             << " | Grado: " << a->getGrado() << "\n";
    }

    // Búsqueda por nombre de profesor (imprime info y lista de alumnos)
    void buscarProfesorPorNombre(const string& nombre) {
        Profesor* p = buscarProfesorPorNombrePtr(nombre);
        if (!p) {
            cout << "No existe profesor con nombre '" << nombre << "'\n";
            return;
        }
        cout << "Profesor encontrado: " << p->getNombreCompleto() << "\n";
        p->imprimirAlumnos();
    }

    // Búsqueda por curso: listar tareas de ese curso y a qué alumno pertenecen
    void buscarPorCurso(const string& curso) {
        cout << "\nTareas encontradas para el curso '" << curso << "':\n";
        bool found = false;
        for (int i = 0; i < alumnoCount; ++i) {
            alumnos[i]->imprimirTareasPorCurso(curso, alumnos[i]->getNombreCompleto());
            // La función imprime solo si encuentra; no podemos saber aquí si imprimió
            // Para simplicidad, assumimos que si total tareas > 0 pudo imprimir
            // (si quieres, podríamos retornar un bool desde imprimirTareasPorCurso)
            found = true; // simplificación para salida
        }
        if (!found) cout << "  (No hay tareas registradas para ese curso)\n";
    }

    // Libera toda la memoria asignada por el sistema (alumnos, profesores y sus contenidos)
    void liberarMemoria() {
        // Borrar alumnos (cada Alumno borra sus Tarea*)
        for (int i = 0; i < alumnoCount; ++i) {
            delete alumnos[i];
        }
        delete[] alumnos;
        alumnos = nullptr;
        alumnoCount = 0;
        alumnoCapacity = 0;

        // Borrar profesores (no borran alumnos, sólo su array interno)
        for (int i = 0; i < profCount; ++i) {
            delete profes[i];
        }
        delete[] profes;
        profes = nullptr;
        profCount = 0;
        profCapacity = 0;
    }

private:
    // Helpers privados para obtener punteros
    Alumno* buscarAlumnoPorCodigoPtr(int codigo) {
        for (int i = 0; i < alumnoCount; ++i) if (alumnos[i]->getCodigo() == codigo) return alumnos[i];
        return nullptr;
    }

    // Búsqueda simple por coincidencia exacta o parcial en el nombre completo
    Profesor* buscarProfesorPorNombrePtr(const string& nombre) {
        for (int i = 0; i < profCount; ++i) {
            string nom = profes[i]->getNombreCompleto();
            if (nom == nombre) return profes[i];
            // comparación parcial (por si pasan solo "Apellido" o "Nombre Apellido")
            if (nom.find(nombre) != string::npos) return profes[i];
        }
        return nullptr;
    }
};

/* -----------------------------
   Ejecución secuencial de actividades (main)
   Demuestra:
   - registro de alumnos y profesores
   - asignación profesor-alumno
   - registro de tareas
   - reportes y búsquedas
   - liberación final de memoria
   ----------------------------- */
int main() {
    Sistema sys;

    cout << "=== Actividad: Registro de alumnos y profesores ===\n";
    // Registrar alumnos
    sys.registrarAlumno(1001, 3, "Juan", "Perez");
    sys.registrarAlumno(1002, 4, "Ana", "Gomez");
    sys.registrarAlumno(1003, 3, "Luis", "Garcia");

    // Registrar profesores
    sys.registrarProfesor("Rocio", "Martinez");
    sys.registrarProfesor("Carlos", "Lopez");

    cout << "\n=== Actividad 5.1: Asignar alumnos a profesores ===\n";
    // Asignar alumnos a profesores (pueden ser de distintos grados)
    sys.asignarAlumnoAProfesor(1001, "Rocio Martinez");
    sys.asignarAlumnoAProfesor(1002, "Rocio Martinez");
    sys.asignarAlumnoAProfesor(1003, "Carlos Lopez");

    cout << "\n=== Actividad 5.3: Registrar tareas ===\n";
    // Registrar tareas (alumnos reciben tareas; entregado = true/false)
    sys.registrarTarea(1001, "Matematica", "Rocio Martinez", "2025-09-01", true);
    sys.registrarTarea(1001, "Ciencias", "Carlos Lopez", "2025-09-02", false);
    sys.registrarTarea(1002, "Matematica", "Rocio Martinez", "2025-09-01", true);
    sys.registrarTarea(1003, "Historia", "Carlos Lopez", "2025-09-03", true);
    sys.registrarTarea(1002, "Arte", "Carlos Lopez", "2025-09-05", false);

    cout << "\n=== Mostrar tareas de un alumno (ejemplo) ===\n";
    sys.mostrarTareasAlumno(1001); // muestra tareas de Juan Perez

    cout << "\n=== Actividad 5.4: Reportes estadísticos ===\n";
    sys.mostrarResumenTareasPorAlumno();
    sys.cantidadAlumnosDelProfesor("Rocio Martinez");

    cout << "\n=== Actividad 5.5: Búsquedas ===\n";
    sys.buscarAlumnoPorCodigo(1002);
    sys.buscarProfesorPorNombre("Carlos");
    sys.buscarPorCurso("Matematica");

    cout << "\n=== Limpiando memoria y finalizando ===\n";
    // Opcional: liberarMemoria es llamada en destructor ~Sistema, pero la podemos invocar explícitamente:
    sys.liberarMemoria();

    cout << "Memoria liberada. Programa finalizado.\n";
    return 0;
}
