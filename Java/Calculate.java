import java.io.IOException;
import java.util.Scanner;

public class Calculate {
    public static void main(String[] args) {
        System.out.println("Hi, java");
        Calculate calc = new Calculate();

        //standart input. One symbol
        char temp = '+';
        try {
            System.out.println("Input Temp: ");
            temp = (char) System.in.read();
        }
        catch (IOException e){
            System.out.println("Error!");
        }

        //Input with help scanner
        Scanner scan = new Scanner(System.in);
        System.out.println("Input key: ");
        char key = scan.next().charAt(0);
        System.out.println("Input a: ");
        double a = scan.nextDouble();
        System.out.println("Input b: ");
        float b = scan.nextFloat();
        double clc = calc.calculate(key, a, b);
        System.out.println(a + " " + key + " " + b +  " = " + clc);
    }
    double calculate(char key, double a, double b){
        switch(key){
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return b == 0 ? -1 : a / b;
        }
        return -1;
    }

}
