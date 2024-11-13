//read and copy the contents of file

import java.io.*;
import java.util.Scanner;

public class FileDisplay {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // Prompt for the source file name
        System.out.print("Enter the source file name: ");
        String sourceFile = scanner.nextLine();
        // Display contents character by character
        displayCharacterByCharacter(sourceFile);
        // Display contents line by line
        displayLineByLine(sourceFile);
    }

    // Method to display file content character by character
    public static void displayCharacterByCharacter(String source) {
        try (FileReader fileReader = new FileReader(source)) {
            int character;
            System.out.println("Displaying contents character by character:");
            while ((character = fileReader.read()) != -1) {
                System.out.print((char) character); // Print each character
            }
            System.out.println(); // Newline after character-by-character display
        } catch (IOException e) {
            System.out.println("An error occurred during character-by-character display: " + e.getMessage());
        }
    }

    // Method to display file content line by line
    public static void displayLineByLine(String source) {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(source))) {
            String line;
            System.out.println("Displaying contents line by line:");
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line); // Print each line
            }
        } catch (IOException e) {
            System.out.println("An error occurred during line-by-line display: " + e.getMessage());
        }
    }
}