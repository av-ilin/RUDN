import static java.lang.Math.random;
import static java.lang.Math.sqrt;

public class Field {
    int n;
    char[][] field;
    Field(int n){
        this.n = n;
        field = new char[n][n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n ; j++)
                field[i][j] = ' ';

        for(int i = 0; i < n * (int)sqrt(n); i++){
            int i_ = (int)(random() * (n - 1) );
            int j_ = (int)(random() * (n - 1) );
            field[i_][j_] = '■';
        }

        for(int i = 0; i < n; i++){
            int i_ = (int)(random() * (n - 1) );
            int j_ = (int)(random() * (n - 1) );
            field[i_][j_] = '+';
        }
    }
    void print(int x, int y){
        System.out.print(". ");
        for(int i = 0; i < n; i++)
            System.out.print("— ");
        System.out.println('.');

        for (int i = 0; i < n; i++){
            System.out.print("| ");
            for (int j = 0; j < n; j++){
                if (i == y && j == x)
                    System.out.print("@" + " ");

                else
                    System.out.print(field[i][j] + " ");
            }
            System.out.print("|");
            System.out.println();
        }

        System.out.print(". ");
        for(int i = 0; i < n; i++)
            System.out.print("— ");
        System.out.println('.');
    }
    void change(int x, int y){
        this.field[y][x] = ' ';
    }
    int count_bonuses(){
        int count = 0;
        for (int i =0; i < n; i++)
            for(int j = 0; j < n; j++)
                if (field[i][j] == '+')
                    count ++;
        return count;
    }
    boolean in_bounce(int x, int y){
        if (x > -1 && x < n)
            if(y > -1 && y < n)
                return true;
        return false;
    }
}
