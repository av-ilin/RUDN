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
        output.setText("Examples: start/stop <mouse, cheese, cat>, exit, game" );
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
        h = main.height - main.s_cpanel;
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
class Mouse extends JPanel{
    Main main;
    final Image mouse = new ImageIcon("mouse.png").getImage();
    int x = 0, y = 0, size = 40;

    Mouse(Main main){
        setBounds(0, 100, main.width, main.height - main.s_cpanel);
        setBackground(new Color(0, 0, 0, 0));
        setVisible(true);
        main.add(this);
        this.main = main;
    }

    public void paintComponent(Graphics g){
        super.paintComponent(g);
        g.drawImage(mouse, x, y,size, size, null);
    }

}
class MouseThread extends Thread{
    Mouse mouse;
    Main main;
    final int step = 10;
    boolean moveFlag = true, threadFlag = true;
    MouseThread(Main main) {
        mouse = new Mouse(main);
        this.main = main;
        start();
    }
    void left(){
        if(mouse.x >= step)
            mouse.x -= step;
        main.repaint();
    }
    void right(){
        if(mouse.x <= mouse.getWidth() - mouse.size)
            if(mouse.x <= mouse.getWidth() - step)
                mouse.x += step;
        main.repaint();
    }
    void up(){
        if(mouse.y >= step)
            mouse.y -= step;
        main.repaint();
    }
    void down(){
        if(mouse.y <= mouse.getHeight() - mouse.size)
            if(mouse.y <= mouse.getHeight() - step)
                mouse.y += step;
        main.repaint();
    }

    double distance(int x1, int y1, int x2, int y2){
        return Math.sqrt( (y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2) );
    }
    int[][] changeDirection(int x, int y){
        int[][] dir = new int[1][2];

        double[] dist = new double[8];
        dist[0] = distance(x, y, mouse.x, mouse.y - step);
        dist[1] = distance(x, y, mouse.x + step, mouse.y - step);
        dist[2] = distance(x, y, mouse.x + step, mouse.y);
        dist[3] = distance(x, y, mouse.x + step, mouse.y + step);
        dist[4] = distance(x, y, mouse.x, mouse.y + step);
        dist[5] = distance(x, y, mouse.x - step, mouse.y + step);
        dist[6] = distance(x, y, mouse.x - step, mouse.y);
        dist[7] = distance(x, y, mouse.x - step, mouse.y - step);

        int i_ = 0;
        for(int i = 0; i < 8; i++)
            if(dist[i] < dist[i_])
                i_ = i;

        switch (i_){
            case 0: dir[0][0] = 0; dir[0][1] = -1; break;
            case 1: dir[0][0] = 1; dir[0][1] = -1; break;
            case 2: dir[0][0] = 1; dir[0][1] = 0; break;
            case 3: dir[0][0] = 1; dir[0][1] = 1; break;
            case 4: dir[0][0] = 0; dir[0][1] = 1; break;
            case 5: dir[0][0] = -1; dir[0][1] = 1; break;
            case 6: dir[0][0] = -1; dir[0][1] = 0; break;
            case 7: dir[0][0] = -1; dir[0][1] = -1; break;
        }

        return dir;
    }
    void move(){
        PointerInfo a = MouseInfo.getPointerInfo();
        Point b = a.getLocation();
        int x = (int) b.getX();
        int y = (int) b.getY();
        y = y - main.s_cpanel;

        x -= mouse.size/2;
        y -= mouse.size/2;

        if( x >= mouse.getWidth() - mouse.size)
            x = mouse.getWidth() - mouse.size;
        if( x <= 0 )
            x = 0;
        if( y >= mouse.getHeight() - mouse.size)
            y = mouse.getHeight() - mouse.size;
        if( y <= 0 )
            y = 0;

        if (Math.abs(mouse.x - x) > step || Math.abs(mouse.y - y) > step) {
            int[][] direction = changeDirection(x, y);
            mouse.x += direction[0][0] * step;
            mouse.y += direction[0][1] * step;
        }
    }

    public void run() {
        while(threadFlag) {
            if(moveFlag)
                move();
            main.repaint();
            try {
                sleep(30);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
class Cheese extends JPanel{
    BufferedImage cheese, baz = null;
    int x, y, size = 30;

    Cheese(Main main){
        setBounds(0, 100, main.width, main.height - main.s_cpanel);
        setBackground(new Color(0, 0, 0, 0));
        setVisible(true);
        main.add(this, 1, 0);
        x = (int)((this.getWidth() - size) * Math.random());
        y = (int)((this.getHeight() - size) * Math.random());
        try {
            cheese = ImageIO.read(new File("cheese.png"));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    void imgBounce(){
        int h = cheese.getHeight();
        int w = cheese.getWidth();
        BufferedImage cheese_ = new BufferedImage(w, h, cheese.getType());

        for(int i = 0; i < w; i++)
            for(int j = 0; j < h; j++)
                cheese_.setRGB(i, j, cheese.getRGB(w -1 - i, j));

        cheese = cheese_;
    }

    void imgBounce2(){
        int h = cheese.getHeight();
        int w = cheese.getWidth();
        BufferedImage cheese_ = new BufferedImage(w, h, cheese.getType());

        for(int i = 0; i < w; i++)
            for(int j = 0; j < h; j++)
                cheese_.setRGB(i, j, cheese.getRGB(w -1 - i, h - 1 - j));

        cheese = cheese_;
    }

    public void paintComponent(Graphics g){
        Graphics2D g2 = (Graphics2D) g;
        super.paintComponent(g2);
        g2.drawImage(cheese, x, y, size,size, null);
        g2.drawImage(baz, x, y, size,size, null);
    }
}
class CheeseThread extends Thread {
    BufferedImage baz;
    Cheese cheese;
    Main main;
    double alpha;
    final int speed = 10;
    boolean moveFlag = true, threadFlag = true;
    CheeseThread(Main main) {
        this.cheese = new Cheese(main);
        this.main = main;
        alpha = Math.random() * 10;
        start();
        try {
            baz = ImageIO.read(new File("bang.png"));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    void baz1(){
        cheese.baz = baz;
        cheese.imgBounce();
        try {
            sleep(50);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        cheese.baz = null;
    }

    void baz2(){
        cheese.baz = baz;
        cheese.imgBounce2();
        try {
            sleep(50);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        cheese.baz = null;
    }

    void move(){
        cheese.x += (int)(speed * Math.cos(alpha));
        cheese.y += (int)(speed * Math.sin(alpha));

        if( cheese.x >= cheese.getWidth() - cheese.size) {
            alpha = alpha + Math.PI - 2 * alpha;
            baz1();
        }
        else if( cheese.x <= 0 ){
            alpha = Math.PI - alpha;
            baz1();
        }

        if( cheese.y >= cheese.getHeight() - cheese.size){
            alpha = -alpha;
            baz2();
        }
        else if( cheese.y <= 0 ){
            alpha = -alpha;
            baz2();
        }
    }

    public void run() {
        while(threadFlag) {
            if(moveFlag)
                move();
            main.repaint();
            try {
                sleep(30);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
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
class CatThread extends Thread{
    Cat cat;
    Main main;
    final int step = 5;
    boolean moveFlag = true, threadFlag = true;
    CatThread(Main main) {
        cat = new Cat(main);
        this.main = main;
        start();
    }
    double distance(int x1, int y1, int x2, int y2){
        return Math.sqrt( (y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2) );
    }
    int[][] changeDirection(int x, int y){
        int[][] dir = new int[1][2];

        double[] dist = new double[8];
        dist[0] = distance(x, y, cat.x, cat.y - step);
        dist[1] = distance(x, y, cat.x + step, cat.y - step);
        dist[2] = distance(x, y, cat.x + step, cat.y);
        dist[3] = distance(x, y, cat.x + step, cat.y + step);
        dist[4] = distance(x, y, cat.x, cat.y + step);
        dist[5] = distance(x, y, cat.x - step, cat.y + step);
        dist[6] = distance(x, y, cat.x - step, cat.y);
        dist[7] = distance(x, y, cat.x - step, cat.y - step);

        int i_ = 0;
        for(int i = 0; i < 8; i++)
            if(dist[i] < dist[i_])
                i_ = i;

        switch (i_){
            case 0: dir[0][0] = 0; dir[0][1] = -1; break;
            case 1: dir[0][0] = 1; dir[0][1] = -1; break;
            case 2: dir[0][0] = 1; dir[0][1] = 0; break;
            case 3: dir[0][0] = 1; dir[0][1] = 1; break;
            case 4: dir[0][0] = 0; dir[0][1] = 1; break;
            case 5: dir[0][0] = -1; dir[0][1] = 1; break;
            case 6: dir[0][0] = -1; dir[0][1] = 0; break;
            case 7: dir[0][0] = -1; dir[0][1] = -1; break;
        }

        return dir;
    }
    void move(){
        int x = main.mouse.mouse.x;
        int y = main.mouse.mouse.y;

        x -= main.mouse.mouse.size/2;
        y -= main.mouse.mouse.size/2;

        if( x >= cat.getWidth() - cat.size)
            x = cat.getWidth() - cat.size;
        if( x <= 0 )
            x = 0;
        if( y >= cat.getHeight() - cat.size)
            y = cat.getHeight() - cat.size;
        if( y <= 0 )
            y = 0;

        if (Math.abs(cat.x - x) > step || Math.abs(cat.y - y) > step) {
            int[][] direction = changeDirection(x, y);
            cat.x += direction[0][0] * step;
            cat.y += direction[0][1] * step;
        }
    }

    public void run() {
        while(threadFlag) {
            if (moveFlag)
                move();
            main.repaint();
            try {
                sleep(30);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
