public abstract class Unit{
    private String name;
    private int x, y;

    Unit(int x, int y){
        this.name = "Unknown";
        this.x = x;
        this.y = y;
    }

    String get_name(){return name;}
    void set_name(String name){this.name = name;}
    int get_x(){return x;}
    void set_x(int x){this.x = x;}
    int get_y(){return y;}
    void set_y(int y){this.y = y;}

    abstract int up(Field field);
    abstract int down(Field field);
    abstract int left(Field field);
    abstract int right(Field field);

    abstract int ultimate(Field field);
}

class Destroyer extends Unit {
    Destroyer(int x, int y){
        super(x, y);
        super.set_name("Destroyer");
    }

    int up(Field field){
        int bonus = 0;
        int y = super.get_y();
        if (y < 1 || field.field[y - 1][super.get_x()] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[y - 1][super.get_x()] == '+')
                bonus++;
            field.change(super.get_x(), y - 1);
            super.set_y(y - 1);
        }
        return bonus;
    }

    int down(Field field){
        int bonus = 0;
        int y = super.get_y();
        if (y > field.n - 2 || field.field[y + 1][super.get_x()] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[y + 1][super.get_x()] == '+')
                bonus++;
            field.change(super.get_x(), y + 1);
            super.set_y(y + 1);
        }
        return bonus;
    }

    int left(Field field){
        int bonus = 0;
        int x = super.get_x();
        if (x < 1 || field.field[super.get_y()][x - 1] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[super.get_y()][x - 1] == '+')
                bonus++;
            field.change(x - 1, super.get_y());
            super.set_x(x - 1);
        }
        return bonus;
    }

    int right(Field field){
        int bonus = 0;
        int x = super.get_x();
        if (x > field.n - 2 || field.field[super.get_y()][x + 1] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[super.get_y()][x + 1] == '+')
                bonus++;
            field.change(x + 1, super.get_y());
            super.set_x(x + 1);
        }
        return bonus;
    }

    int ultimate(Field field){
        int x = super.get_x();
        int y = super.get_y();
        for (int i = x - 1; i < x + 2; i++)
            for(int j = y - 1; j < y + 2; j++)
                if(field.in_bounce(i, j))
                    if (field.field[j][i] == '■')
                        field.change(i, j);
        return 0;
    }
}

class Wizard extends Unit{
    Wizard(int x, int y){
        super(x, y);
        super.set_name("Wizard");
    }

    int up(Field field){
        int bonus = 0;
        int y = super.get_y();
        if (y < 1 || field.field[y - 1][super.get_x()] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[y - 1][super.get_x()] == '+')
                bonus++;
            field.change(super.get_x(), y - 1);
            super.set_y(y - 1);
        }
        return bonus;
    }

    int down(Field field){
        int bonus = 0;
        int y = super.get_y();
        if (y > field.n - 2 || field.field[y + 1][super.get_x()] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[y + 1][super.get_x()] == '+')
                bonus++;
            field.change(super.get_x(), y + 1);
            super.set_y(y + 1);
        }
        return bonus;
    }

    int left(Field field){
        int bonus = 0;
        int x = super.get_x();
        if (x < 1 || field.field[super.get_y()][x - 1] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[super.get_y()][x - 1] == '+')
                bonus++;
            field.change(x - 1, super.get_y());
            super.set_x(x - 1);
        }
        return bonus;
    }

    int right(Field field){
        int bonus = 0;
        int x = super.get_x();
        if (x > field.n - 2 || field.field[super.get_y()][x + 1] == '■')
            System.out.println("Sorry! It is impossible!");
        else{
            if(field.field[super.get_y()][x + 1] == '+')
                bonus++;
            field.change(x + 1, super.get_y());
            super.set_x(x + 1);
        }
        return bonus;
    }

    int ultimate(Field field){
        int b_score = 0;
        int x = super.get_x();
        int y = super.get_y();
        for (int i = x - 1; i < x + 2; i++)
            for(int j = y - 1; j < y + 2; j++)
                if(field.in_bounce(i, j))
                    if(field.field[j][i] == '+'){
                        field.change(i, j);
                        b_score++;
                    }
        return b_score;
    }
}
