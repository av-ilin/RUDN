import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        Main main = new Main();
        main.print_instructions();

        Scanner scan = new Scanner(System.in);
        System.out.print("Input nickname: ");
        String nik = scan.nextLine();
        System.out.print("Input size of Field (Example, 10): ");
        int n = scan.nextInt();
        System.out.println("Choose a unit: 0.Destroyer    1.Wizard");
        System.out.print("Input: ");
        boolean u = scan.nextInt() == 1;

        Field field = new Field(n);

        int start_x = 0, start_y = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
                if(field.field[i][j] == ' '){
                    start_y = i;
                    start_x = j;
                    break;
                }
            if(start_x != 0 || start_y != 0)
                break;
        }

        Unit unit;// = new Destroyer(0, 0);
        if(u)
            unit = new Wizard(start_x, start_y);
        else
            unit = new Destroyer(start_x, start_y);

        int score = main.play(field, unit);
        System.out.println(nik + ": " + score);

    }
    void print_instructions(){
        System.out.println("Rules:");
        System.out.println("1. Choose a nickname.");
        System.out.println("2. Choose the size of the field.");
        System.out.println("3. Choose a unit.");
        System.out.println("* The Destroyer can destroy an obstacle.");
        System.out.println("* The Wizard can collect bonuses within a radius of 1 cell.");
        System.out.println("4. Collect all the bonuses in the minimum number of steps!");
        System.out.println("+ bonus     ■ obstacle");
        System.out.println("3...2...1...Start!");
    }
    int play(Field field, Unit unit){
        int count_b = field.count_bonuses();
        int score = 0, step = 0;
        System.out.println("w.Up   s.Down   a.Left   d.Right");
        Scanner scan = new Scanner(System.in);
        while(true){
            field.print(unit.get_x(), unit.get_y());
            System.out.print("Input: ");
            char key = scan.next().charAt(0);
            switch (key){
                case 'w': score += unit.up(field); break;
                case 's': score += unit.down(field); break;
                case 'a': score += unit.left(field); break;
                case 'd': score += unit.right(field); break;
                case 'o': return 0;
                default: break;
            }
            step++;

            if (step % 3 == 0){
                field.print(unit.get_x(), unit.get_y());
                System.out.println("Ultimate time!");
                score += unit.ultimate(field);
            }

            if(score >= count_b)
                break;
        }
        field.print(unit.get_x(), unit.get_y());
        return step;
    }

}
