package gui;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import java.util.*;

public class JanelaListagem extends JFrame {
	private JTextArea texto;
	private List<?> listagem;
	
	public JanelaListagem(List<?> l) {
		super("Listagem");
		listagem = l;
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		texto = new JTextArea();
		preencher();
		JScrollPane painelRolagem = new JScrollPane(texto);
		getContentPane().add(painelRolagem);
		setBounds(20, 20, 200, 100);
	}
	
	private void preencher() {
		for(Object o : listagem) {
			texto.append(o.toString() + "\r\n");
		}
	}
}
