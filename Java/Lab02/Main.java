import javax.swing.*;
import java.awt.*;
public class Main extends JFrame{
    final private int width = 600;
    final int height = 373;
    final private Image img = new ImageIcon("img.jpg").getImage();
    Arrangement arrangement;
    Console cli;
    int x = 180;
    Main(){
        super("Code&Cats");
        setBounds(380, 100, width,height);
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        arrangement = new Arrangement(this);
        cli = new Console(this);
        setVisible(true);
    }

    public static void main(String[] args){
        Main frame = new Main();
    }

    public void paint(Graphics g){
        super.paint(g);
        g.setColor(Color.BLACK);
        g.drawLine(0,132,width, 132);
        g.drawImage(img, x, 132, null);
    }

}