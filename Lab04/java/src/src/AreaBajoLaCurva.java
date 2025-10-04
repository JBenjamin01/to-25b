import java.util.*;
public class Trapecio{
    static double area(double a, double b, double h){
        double area = ((a + b) * h) / 2;
        return area;
    }
}

class Worker extends Thread {
    private double a, b, rango, area;

    public Worker(double a, double b, double rango) {
        this.a = a;
        this.b = b;
        this.rango = rango;
        this.area = 0;
    }

    private double hallarPunto(double x) {
        return 2 * Math.pow(x, 2) + 3 * x + 1 / 2.0;
    }

    @Override
    public void run() {
        System.out.println("Hilo de " + this.a + " a " + this.b + " iniciado");
        double a1 = a;
        while (a1 < b) {
            double y1 = hallarPunto(a1);
            double y2 = hallarPunto(a1 + this.rango);
            this.area += Trapecio.area(y1, y2, this.rango);
            a1 += this.rango;
        }

    }

    public double getArea() {
        return this.area;
    }

}

public class AreaBajoLaCurva{
    
    public static double rango(double a, double b, int num){
        return (b - a)*1.0/num;
    }
    public static double subrango(double r, int h){
        return r / h;
    }

    public static void main(String[] args) {
        int numHilos = 5;
        int numTrapecios = 100;
        double a = 0;
        double b = 10;
        double rango = rango(a, b, numTrapecios);
        double subRango = (b - a) / numHilos;
        Worker[] hilos = new Worker[numHilos];

        for (int i = 0; i < numHilos; i++) {
            double li = a + i * subRango;
            double ls = li + subRango;
            hilos[i] = new Worker(li, ls, rango);
            hilos[i].start();

        }

        double area = 0;
        for (Worker w : hilos) {
            try {
                w.join();
            } catch (InterruptedException e) {
                System.err.println("Hilo interrumpido");
            }
            area += w.getArea();
        }

        System.out.println("El area bajo la curva es: " + area);

    }
}