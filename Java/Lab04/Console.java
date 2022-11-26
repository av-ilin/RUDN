import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Console{
    Main main;
    Console(Main main){
        this.main = main;
    }
    void output(){
        String text = main.arrangement.input.getText();
        String[] split_text = text.split(" ");
        String key1 = "", key2 = "";
        if (split_text.length > 0)
            key1 = split_text[0];
        if (split_text.length > 1)
            key2 = split_text[1];

        if (key1.equals("start"))
            switch (key2){
                case "mouse": main.mouse.moveFlag = true; break;
                case "cat": main.cat.moveFlag = true; break;
                case "cheese":
                    for(int i = 0; i < main.cheese.size(); i++)
                        main.cheese.get(i).moveFlag = true;
                    break;
            }

        if (key1.equals("stop"))
            switch (key2){
                case "mouse": main.mouse.moveFlag = false; break;
                case "cat": main.cat.moveFlag = false; break;
                case "cheese":
                    for(int i = 0; i < main.cheese.size(); i++)
                        main.cheese.get(i).moveFlag = false;
                    break;
            }

        if(key1.equals("exit"))
            System.exit(0);

        if(key1.equals("game"))
            main.game.play = true;

        main.arrangement.input.setText("");
        main.arrangement.output.setText("Examples: start/stop <mouse, cheese, cat>, exit, game\n>> " + text);
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
            case 65: main.mouse.left(); break;
            case 87: main.mouse.up(); break;
            case 68: main.mouse.right(); break;
            case 83: main.mouse.down(); break;
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
