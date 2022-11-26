import javax.swing.*;
import java.awt.*;

public class Arrangement{
    JButton button;
    JTextField input;
    JTextArea output;
    Arrangement(Main main){
        main.addKeyListener(new Key_Listener(main));
        main.setFocusable(true);

        button = new JButton("Input");
        button.setBounds(0, 0, 100, 50);
        button.addActionListener(new Button_Listener(main));
        button.setFocusable(false);
        button.setFont(new Font("Times New Roman", Font.BOLD, 15));
        main.add(button);

        input = new JTextField();
        input.setBounds(100, 0, 500, 50);
        input.setVisible(true);
        input.setFont(new Font("Times New Roman", Font.PLAIN, 15));
        main.add(input);

        output = new JTextArea();
        output.setBounds(0, 50, 600, 50);
        output.setVisible(true);
        output.setEnabled(false);
        output.setFont(new Font("Times New Roman", Font.ITALIC, 15));
        output.setDisabledTextColor(Color.BLACK);
        output.setText("Examples: Right, Left");
        main.add(output);
    }
}
