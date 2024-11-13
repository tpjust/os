//  Oprand error in a given job

// Define a custom exception to simulate an operand error interrupt
class OperandError extends Exception {
    public OperandError(String message) {
        super(message);
    }
}

public class OperandErrorCheck {

    // Function to check for operand errors in a job
    public static void checkOperandError(String[][] operations) throws OperandError {
        for (int i = 0; i < operations.length; i++) {
            try {
                String operator = operations[i][0];
                double operand1 = Double.parseDouble(operations[i][1]);
                double operand2 = Double.parseDouble(operations[i][2]);

                // Simulate different operations and check for errors
                double result = 0;
                switch (operator) {
                    case "add":
                        result = operand1 + operand2;
                        break;
                    case "subtract":
                        result = operand1 - operand2;
                        break;
                    case "multiply":
                        result = operand1 * operand2;
                        break;
                    case "divide":
                        if (operand2 == 0) {
                            throw new OperandError("Operand error in operation " + i + ": Division by zero");
                        }
                        result = operand1 / operand2;
                        break;
                    default:
                        throw new OperandError(
                                "Operand error in operation " + i + ": Undefined operator '" + operator + "'");
                }

                // Output the result of the operation
                System.out.println("Operation " + i + " (" + operator + "): " + operand1 + " " + operator + " "
                        + operand2 + " = " + result);
            } catch (NumberFormatException e) {
                // Handle invalid operand types (e.g., non-numeric strings)
                throw new OperandError("Operand error in operation " + i + ": Incompatible operand types.");
            }
        }
    }

    public static void main(String[] args) {
        // Define a set of operations (operator, operand1, operand2)
        String[][] operations = {
                { "add", "10", "5" }, // Valid operation
                { "subtract", "7", "3" }, // Valid operation
                { "divide", "8", "0" }, // Division by zero (operand error)
                { "multiply", "6", "two" }, // Invalid operand type (operand error)
                { "add", "4", "2" }, // Valid operation
                { "mod", "5", "2" } // Undefined operator (operand error)
        };

        // Run the check and handle the operand error interrupt
        try {
            checkOperandError(operations);
        } catch (OperandError e) {
            System.out.println("Interrupt: " + e.getMessage());
        }
    }
}