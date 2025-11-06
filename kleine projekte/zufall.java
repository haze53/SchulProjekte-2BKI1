import java.util.Scanner;

public class zufall {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("Geben Sie die untere Grenze ein:");
        int min = input.nextInt();
        System.out.println("Geben Sie die obere Grenze ein:");
        int max = input.nextInt();
        int zahl = (int) (Math.random() * (max - min)) + min;
        System.out.println("Geben Sie eine Zahl zwischen " + min + " und " + max + " ein:");

        while (true) {
        int userInput = input.nextInt();
         if (userInput > zahl) {
            System.out.println("Die eingegebene Zahl ist größer als die zufällige Zahl.");
            } else if (userInput < zahl) {
            System.out.println("Die eingegebene Zahl ist kleiner als die zufällige Zahl.");
            } else {
            System.out.println("Glückwunsch! Sie haben die richtige Zahl erraten: " + zahl);
            break;
            }

        }

        input.close();
    }
}
