import javax.swing.*;
import java.awt.*;
public class Main extends JFrame{
    final int width = 600, height = 400, s_cpanel = 130;
    Arrangement arrangement;
    Console cli;
    MouseThread mse;
    CatThread cat;
    Back back;

    Main(){
        super("Code&Cats");
        setBounds(0, 0, width, height);
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        arrangement = new Arrangement(this);
        cli = new Console(this);
        mse = new MouseThread(this);
        cat = new CatThread(this);
        back = new Back(this);

        setVisible(true);
    }

    public static void main(String[] args){
        Main frame = new Main();
        frame.status();
    }

    public void paint(Graphics g){
        super.paint(g);
        g.setColor(Color.WHITE);
        g.drawLine(0,s_cpanel, width, s_cpanel);
    }

    void status(){
        System.out.println("Status: Ok");
    }
}