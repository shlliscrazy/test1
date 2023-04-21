import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.util.Scanner;

public class AESEncrytion 
{
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter plaintext (e.g. HELLOAES12345): ");
        String plaintext = scanner.nextLine();
        System.out.print("Enter key (human-readable key): ");
        String key = scanner.nextLine();

        // Use default IV key
        String iv = "gaijinentertaimn";
        byte[] ivBytes = iv.getBytes(StandardCharsets.UTF_8);

        // Convert key to bytes
        byte[] keyBytes = key.getBytes(StandardCharsets.UTF_8);

        // Create AES key and IV
        SecretKeySpec secretKeySpec = new SecretKeySpec(keyBytes, "AES");
        IvParameterSpec ivParameterSpec = new IvParameterSpec(ivBytes);

        // Create AES cipher in CBC mode
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, secretKeySpec, ivParameterSpec);

        // Encrypt the plaintext
        byte[] ciphertext = cipher.doFinal(plaintext.getBytes(StandardCharsets.UTF_8));

        // Print the ciphertext
        System.out.println("Plaintext: " + plaintext);
        System.out.println("Key: " + key);
        System.out.println("IV: " + iv);
        System.out.println("Ciphertext: " + Base64.getEncoder().encodeToString(ciphertext));

        // Decrypt the ciphertext
        cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, ivParameterSpec);
        byte[] decryptedBytes = cipher.doFinal(ciphertext);

        // Convert decrypted bytes to plaintext
        String decryptedPlaintext = new String(decryptedBytes, StandardCharsets.UTF_8);

        // Print the decrypted plaintext
        System.out.println("Decrypted Plaintext: " + decryptedPlaintext);

        scanner.close();
    }
}
