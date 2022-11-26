import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Console {
    Main main;
    Console(Main main){
        this.main = main;
    }
    void output(){
        String text = main.arrangement.input.getText();

        if(text.equals("StartMouse"))
            main.mse.moveFlag = true;
        if(text.equals("StopMouse"))
            main.mse.moveFlag = false;
        if(text.equals("StartCat"))
            main.cat.moveFlag = true;
        if(text.equals("StopCat"))
            main.cat.moveFlag = false;
        if(text.equals("Exit"))
            System.exit(0);

        main.arrangement.input.setText("");
        main.arrangement.output.setText("Examples: StartMouse, " +
                "StartCat, StopMouse, StopCat, Exit" + "\n>>" + text);
        main.requestFocus();
    }

}

class Button_Listener implements ActionListener {
    Main main;
    Button_Listener(Main main){
        this.main = main;
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        String key = e.getActionCommand();
        if(key.equals("Input"))
            main.cli.output();
    }
}

class KeyBoard_Listener implements KeyListener{
    Main main;
    KeyBoard_Listener(Main main){
        this.main = main;
    }

    public void keyPressed(KeyEvent e) {
        int key_ = e.getKeyCode();
        switch (key_){
            case 65: main.cat.left(); break;
            case 87: main.cat.up(); break;
            case 68: main.cat.right(); break;
            case 83: main.cat.down(); break;
            case 81: main.arrangement.input.requestFocus(); break;
            case 69: System.exit(0);
            default:
                System.out.println(key_); break;
        }
    }
    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e) {}
}

class Input_Listener implements KeyListener{
    Main main;
    Input_Listener(Main main){
        this.main = main;
    }

    public void keyPressed(KeyEvent e) {
        int key_ = e.getKeyCode();
        if (key_ == 10)
            main.cli.output();

    }

    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e) {}
}

class MouseThread extends Thread {
    BufferedImage baz;
    Mouse mouse;
    Main main;
    double alpha;
    final int speed = 10;
    boolean moveFlag = true;
    MouseThread(Main main) {
        this.mouse = new Mouse(main);
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
        mouse.baz = baz;
        mouse.imgBounce();
        mouse.baz = null;
    }

    void baz2(){
        mouse.baz = baz;
        mouse.imgBounce2();
        mouse.baz = null;
    }

    void move(){
        mouse.x += (int)(speed * Math.cos(alpha));
        mouse.y += (int)(speed * Math.sin(alpha));

        if( mouse.x >= mouse.getWidth() - mouse.size) {
            alpha = alpha + Math.PI - 2 * alpha;
            baz1();
        }
        else if( mouse.x <= 0 ){
            alpha = Math.PI - alpha;
            baz1();
        }

        if( mouse.y >= mouse.getHeight() - mouse.size){
            alpha = -alpha;
            baz2();
        }
        else if( mouse.y <= 0 ){
            alpha = -alpha;
            baz2();
        }
    }

    public void run() {
        while(true) {
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

class CatThread extends Thread{
    Cat cat;
    Main main;
    final int step = 5;
    boolean moveFlag = true;
    CatThread(Main main) {
        cat = new Cat(main);
        this.main = main;
        start();
    }
    void left(){
        if(cat.x >= step)
            cat.x -= step;
        main.repaint();
    }
    void right(){
        if(cat.x <= cat.getWidth() - cat.size)
            if(cat.x <= cat.getWidth() - step)
                cat.x += step;
        main.repaint();
    }
    void up(){
        if(cat.y >= step)
            cat.y -= step;
        main.repaint();
    }
    void down(){
        if(cat.y <= cat.getHeight() - cat.size)
            if(cat.y <= cat.getHeight() - step)
                cat.y += step;
        main.repaint();
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
        PointerInfo a = MouseInfo.getPointerInfo();
        Point b = a.getLocation();
        int x = (int) b.getX();
        int y = (int) b.getY();
        y = y - main.s_cpanel;

        x -= cat.size/2;
        y -= cat.size/2;

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
        while(true) {
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
