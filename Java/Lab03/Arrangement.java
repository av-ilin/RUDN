import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.BufferedImageOp;
import java.awt.image.ConvolveOp;
import java.awt.image.Kernel;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;

public class Arrangement{
    JButton button;
    JTextField input;
    JTextArea output;
    Arrangement(Main main){
        main.addKeyListener(new KeyBoard_Listener(main));
        main.setFocusable(true);

        button = new JButton("Input");
        button.setBounds(0, 0, 100, 50);
        button.addActionListener(new Button_Listener(main));
        button.setFocusable(false);
        button.setFont(new Font("Times New Roman", Font.BOLD, 15));
        button.setBackground(Color.BLACK);
        button.setForeground(Color.WHITE);
        button.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        main.add(button);

        input = new JTextField();
        input.setBounds(100, 0, 500, 50);
        input.setVisible(true);
        input.setFont(new Font("Times New Roman", Font.PLAIN, 15));
        input.addKeyListener(new Input_Listener(main));
        input.setBackground(Color.BLACK);
        input.setForeground(Color.GREEN);
        input.setCursor(Cursor.getPredefinedCursor(Cursor.TEXT_CURSOR));
        //input.setCaret(new Caret());
        main.add(input);

        output = new JTextArea();
        output.setBounds(0, 50, 600, 50);
        output.setVisible(true);
        output.setEnabled(false);
        output.setFont(new Font("Times New Roman", Font.ITALIC, 15));
        output.setText("Examples: StartMouse, StartCat, StopMouse, StopCat, Exit");
        output.setBackground(Color.BLACK);
        output.setDisabledTextColor(Color.GREEN);
        main.add(output);
    }
}

class Back extends JPanel{
    BufferedImage back;
    int w, h;

    final int blur_radius = 20;
    Back(Main main){
        w = main.width;
        h = main.height - 130;
        setBounds(0, 100, w, h);
        setBackground(Color.BLACK);
        setVisible(true);
        main.add(this);
        try {
            back = ImageIO.read(new File("background.jpg"));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        blurImg();
    }

    void blurImg(){
        float weight = 1.0f / (blur_radius * blur_radius);
        float[] data = new float[blur_radius * blur_radius];
        Arrays.fill(data, weight);

        Kernel kernel = new Kernel(blur_radius, blur_radius, data);
        BufferedImageOp op = new ConvolveOp(kernel, ConvolveOp.EDGE_NO_OP, null);
        back = op.filter(back, null);
    }

    public void paintComponent(Graphics g){
        Graphics2D g2 = (Graphics2D) g;
        super.paintComponent(g2);
        g2.drawImage(back, 0, 0, w, h, null);
    }
}

class Cat extends JPanel{
    Main main;
    final Image cat = new ImageIcon("cat.png").getImage();
    int x = 265, y = 100, size = 70;

    Cat(Main main){
        setBounds(0, 100, main.width, main.height - main.s_cpanel);
        setBackground(new Color(0, 0, 0, 0));
        setVisible(true);
        main.add(this);
        this.main = main;
    }

    public void paintComponent(Graphics g){
        super.paintComponent(g);
        g.drawImage(cat, x, y,size, size, null);
    }

}

class Mouse extends JPanel{
    BufferedImage mouse, baz = null;
    int x, y, size = 35;

    Mouse(Main main){
        setBounds(0, 100, main.width, main.height - main.s_cpanel);
        setBackground(new Color(0, 0, 0, 0));
        setVisible(true);
        main.add(this);
        x = (int)((this.getWidth() - size) * Math.random());
        y = (int)((this.getHeight() - size) * Math.random());
        try {
            mouse = ImageIO.read(new File("mouse.png"));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    void imgBounce(){
        int h = mouse.getHeight();
        int w = mouse.getWidth();
        BufferedImage mouse_ = new BufferedImage(w, h, mouse.getType());

        for(int i = 0; i < w; i++)
            for(int j = 0; j < h; j++)
                mouse_.setRGB(i, j, mouse.getRGB(w -1 - i, j));

        mouse = mouse_;
    }

    void imgBounce2(){
        int h = mouse.getHeight();
        int w = mouse.getWidth();
        BufferedImage mouse_ = new BufferedImage(w, h, mouse.getType());

        for(int i = 0; i < w; i++)
            for(int j = 0; j < h; j++)
                mouse_.setRGB(i, j, mouse.getRGB(w -1 - i, h - 1 - j));

        mouse = mouse_;
    }

    public void paintComponent(Graphics g){
        Graphics2D g2 = (Graphics2D) g;
        super.paintComponent(g2);
        g2.drawImage(mouse, x, y, size,size, null);
        g2.drawImage(baz, x, y, size,size, null);
    }
}

