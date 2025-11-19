package Funktionen;



public class funcion_1 {
    public static void main(String[] args) {
        int ergebnis = test(5);
        System.out.println("Das Ergebnis ist: " + ergebnis);
    }

    public static int test(int x) {
            if (x > 0) {
            return x * test(x - 1);
        } else {
            return 1;
            }
        }
    }   

