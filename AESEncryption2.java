import java.awt.*;
import java.awt.event.*;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import javax.swing.*;

public class AESEncryption2 extends JPanel
{
    private JTextField plaintext;
    private JTextArea key;
    private JTextArea iv;
    private JLabel plaintextlabel;
    private JLabel keylabel;
    private JLabel ivlabel;
    private JButton encryptlabel;
    private JTextField jcomp8;
    private JLabel ciphertext;
    private JTextField decrypted;
    private JLabel decryptedlabel;
    private JButton readfile;

    public AESEncryption2() 
    {
        //construct components
        plaintext = new JTextField (5);
        key = new JTextArea (5, 5);
        iv = new JTextArea (5, 5);
        plaintextlabel = new JLabel ("plain text");
        keylabel = new JLabel ("key");
        ivlabel = new JLabel ("IV key");
        encryptlabel = new JButton ("encrypt and save to a file lol");
        jcomp8 = new JTextField (5);
        ciphertext = new JLabel ("cipher text");
        decrypted = new JTextField (5);
        decryptedlabel = new JLabel ("decrypted");
        readfile = new JButton ("Read encrypted file");

        //adjust size and set layout
        setPreferredSize (new Dimension (944, 649));
        setLayout (null);
        
        //set components properties
        readfile.setToolTipText ("READ THE FUCKING ENCRYPTED FILE");

        //add components
        add (plaintext);
        add (key);
        add (iv);
        add (plaintextlabel);
        add (keylabel);
        add (ivlabel);
        add (encryptlabel);
        add (jcomp8);
        add (ciphertext);
        add (decrypted);
        add (decryptedlabel);
        add (readfile);

        //set component bounds (only needed by Absolute Positioning)
        plaintext.setBounds (370, 190, 215, 40);
        key.setBounds (370, 255, 210, 40);
        iv.setBounds (370, 325, 215, 50);
        plaintextlabel.setBounds (370, 160, 100, 25);
        keylabel.setBounds (370, 230, 100, 25);
        ivlabel.setBounds (370, 300, 100, 25);
        encryptlabel.setBounds (400, 380, 200, 25);
        jcomp8.setBounds (365, 440, 215, 65);
        ciphertext.setBounds (365, 415, 100, 25);
        decrypted.setBounds (360, 540, 180, 60);
        decryptedlabel.setBounds (360, 510, 100, 25);
        readfile.setBounds (405, 620, 160, 30);

        encryptlabel.addActionListener(new ActionListener() 
        {
            public void actionPerformed(ActionEvent e) 
            {
                
                try 
                {
                    String plainString = plaintext.getText();
                    String keyString = key.getText();
                    String ivString = iv.getText();

                    // convert key and iv strings to byte arrays
                    byte[] keyBytes = keyString.getBytes(StandardCharsets.UTF_8);
                    byte[] ivBytes = ivString.getBytes(StandardCharsets.UTF_8);

                    // create secret key and iv specs from byte arrays
                    SecretKeySpec secretKeySpec = new SecretKeySpec(keyBytes, "AES");
                    IvParameterSpec ivSpec = new IvParameterSpec(ivBytes);

                    // create cipher and set to encrypt mode
                    Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
                    cipher.init(Cipher.ENCRYPT_MODE, secretKeySpec, ivSpec);

                    // encrypt the plaintext
                    byte[] encryptedBytes = cipher.doFinal(plainString.getBytes());
                    jcomp8.setText(Base64.getEncoder().encodeToString(encryptedBytes));

                    // write the encrypted text to a file
                    BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("encrypted.txt"));
                    byte[] encryptedData = Base64.getEncoder().encode(encryptedBytes);
                    bos.write(encryptedData);
                    bos.close();

                    // decrypt the plaintext
                    cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, ivSpec);
                    byte[] decryptedBytes = cipher.doFinal(encryptedBytes);
                    decrypted.setText(new String(decryptedBytes));

                }
                catch (Exception ex) 
                {
                    JOptionPane.showMessageDialog(AESEncryption2.this, ex.getMessage(),"Encryption Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        readfile.addActionListener(new ActionListener() 
        {
            public void actionPerformed(ActionEvent e) 
            {
                try 
                {
                    // read the encrypted data from the file
                    byte[] encryptedData = Files.readAllBytes(Paths.get("encrypted.txt"));
                    jcomp8.setText(new String(encryptedData));

                    // decode the encrypted data from Base64
                    byte[] encryptedBytes = Base64.getDecoder().decode(encryptedData);

                    // get the key and iv values from the text areas
                    String keyString = key.getText();
                    String ivString = iv.getText();
        
                    // convert key and iv strings to byte arrays
                    byte[] keyBytes = keyString.getBytes(StandardCharsets.UTF_8);
                    byte[] ivBytes = ivString.getBytes(StandardCharsets.UTF_8);
        
                    // create secret key and iv specs from byte arrays
                    SecretKeySpec secretKeySpec = new SecretKeySpec(keyBytes, "AES");
                    IvParameterSpec ivSpec = new IvParameterSpec(ivBytes);
        
                    // create cipher and set to decrypt mode
                    Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
                    cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, ivSpec);
        
                    // decrypt the ciphertext
                    byte[] decryptedBytes = cipher.doFinal(encryptedBytes);
                    decrypted.setText(new String(decryptedBytes));
        
                } 
                catch (Exception ex) 
                {
                    JOptionPane.showMessageDialog(AESEncryption2.this, ex.getMessage(),"Decryption Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    public static void main (String[] args) 
    {
        JFrame frame = new JFrame ("YEAHH v4.6");
        frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add (new AESEncryption2());
        frame.pack();
        frame.setVisible (true);
    }
}
