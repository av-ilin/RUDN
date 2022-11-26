import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class Main extends JFrame{
    final int width = 600, height = 400, s_cpanel = 130;
    Arrangement arrangement;
    Console cli;
    MouseThread mouse;
    ArrayList<CheeseThread> cheese;
    CatThread cat;
    Back back;
    GameThread game;
    Main(){
        super("Code&Cats");
        setBounds(0, 0, width, height);
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        arrangement = new Arrangement(this);
        cli = new Console(this);
        mouse = new MouseThread(this);
        cheese = new ArrayList();
        for(int i = 0; i < 5; i++)
            cheese.add(new CheeseThread(this));
        cat = new CatThread(this);
        back = new Back(this);

        game = new GameThread();

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
    class GameThread extends Thread{
        boolean threadFlag, play;
        GameThread(){
            threadFlag = true;
            play = false;
            start();
        }
        public void run() {
            while(threadFlag){
                if (play)
                    game();

                try {
                    sleep(30);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
        void pause(long second){
            try {
                sleep(second * 1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        void begin(){
            cat.moveFlag = false;
            mouse.moveFlag = false;
            mouse.mouse.x = 0;
            mouse.mouse.y = 0;
            cat.cat.x = cat.cat.getWidth() - cat.cat.size;
            cat.cat.y = cat.cat.getHeight() - cat.cat.size;
            arrangement.output.setText("Are you ready?");
            pause(2);
            for(int i = 3; i > 0; i--){
                arrangement.output.setText( i + "...");
                pause(1);
            }
            arrangement.output.setText("Start!");
            mouse.moveFlag = true;
            cat.moveFlag = true;
        }
        void game(){
            begin();
            boolean win = true;
            while(cheese.size() > 0){
                int radius = mouse.mouse.size;
                int mouse_x = mouse.mouse.x;
                int mouse_y = mouse.mouse.y;
                int cat_x = cat.cat.x;
                int cat_y = cat.cat.y;

                int dx = Math.abs(mouse_x - cat_x);
                int dy = Math.abs(mouse_y - cat_y);

                if( dx < radius && dy < radius){
                    arrangement.output.setText("You lose!");
                    win = false;
                    break;
                }

                for(int i = 0; i < cheese.size(); i++){
                    int cheese_x = cheese.get(i).cheese.x;
                    int cheese_y = cheese.get(i).cheese.y;
                    dx = Math.abs(mouse_x - cheese_x);
                    dy = Math.abs(mouse_y - cheese_y);

                    if( dx < radius && dy < radius){
                        arrangement.output.setText("Yep!");
                        cheese.get(i).threadFlag = false;
                        cheese.get(i).cheese.cheese = null;
                        cheese.remove(i);
                        break;
                    }
                }
            }
            if(win)
                arrangement.output.setText("You won!");
            for(CheeseThread cheeseThread : cheese) {
                cheeseThread.threadFlag = false;
                cheeseThread.cheese.cheese = null;
                cheeseThread.cheese.baz = null;
            }
            pause(3);
            backFrame();
        }
        void backFrame(){
            arrangement.output.setText("Examples: start/stop <mouse, cheese, cat>, exit, game" + "\n>>game");
            cheese.clear();
            for(int i = 0; i < 5; i++)
                cheese.add(new CheeseThread(cli.main));
            play = false;
        }
    }
}