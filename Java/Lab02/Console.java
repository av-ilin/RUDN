import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Console {
    Main main;
    Console(Main main){
        this.main = main;
    }
    void output(){
        String text = main.arrangement.input.getText();

        if(text.equals("Left"))
            left();
        if(text.equals("Right"))
            right();

        main.arrangement.output.setText("Output: " + text);
        main.requestFocus();
    }
    void left(){
        if(main.x > -209)
            main.x -= 30;
        else
            main.x = main.getWidth() - 30;
        main.repaint();
    }
    void right(){
        if(main.x < main.getWidth())
            main.x += 30;
        else
            main.x = -179;
        main.repaint();
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

class Key_Listener implements KeyListener{
    Main main;
    Key_Listener(Main main){
        this.main = main;
    }

    public void keyPressed(KeyEvent e) {
        int key_ = e.getKeyCode();
        if(key_ == 37)
            main.cli.left();
        if(key_ == 39)
            main.cli.right();
    }
    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e) {}
}