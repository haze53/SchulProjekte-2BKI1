import java.util.Scanner;

public class verzweigung2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Bitte geben Sie einen Text ein: ");
        String eingabe = scanner.nextLine();
        int text_length = eingabe.length();


        if  (text_length < 5){
            System.out.println("Der eingegebene Text ist kleiner als 5 Zeichen.");
        } else if (text_length <= 15) {
            System.out.println("Der eingegebene Text ist zwischen 5 und 15 Zeichen.");
        } else {
            System.out.println("Der eingegebene Text ist länger als 15 Zeichen.");
        }

    }
}