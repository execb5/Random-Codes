package dados;

import negocio.CadastroDAO;
import java.util.ArrayList;
import java.util.List;
import negocio.Pessoa;

/**
 *
 * @author Julio
 */
public class CadastroMem implements CadastroDAO {
    private List<Pessoa> pessoas;

    public CadastroMem() {
        pessoas = new ArrayList<>();
    }

    public boolean adicionar(Pessoa p) {
        return pessoas.add(p);
    }

    public List<Pessoa> getHomens() {
        List<Pessoa> tmp = new ArrayList<>();
        for (Pessoa p : pessoas) {
            if (p.getSexo() == 'M') {
                tmp.add(p);
            }
        }
        return tmp;
    }

    public List<Pessoa> getMulheres() {
        List<Pessoa> tmp = new ArrayList<>();
        for (Pessoa p : pessoas) {
            if (p.getSexo() == 'F') {
                tmp.add(p);
            }
        }
        return tmp;
    }

    public List<Pessoa> getTodos() {
        return pessoas;
    }

    public Pessoa getPessoaPorNome(String n) {
        for(Pessoa p : pessoas) {
            if(p.getNome().equalsIgnoreCase(n))
                return p;
        }
        return null;
    }
}
