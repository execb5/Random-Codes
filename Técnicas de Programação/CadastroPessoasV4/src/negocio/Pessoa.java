package negocio;

public class Pessoa {
    private String nome;
    private char sexo;

    public Pessoa(String umNome, boolean masculino) {
        nome = umNome;
        if (masculino) {
            sexo = 'M';
        } else {
            sexo = 'F';
        }
    }

    public String getNome() {
        return nome;
    }

    public char getSexo() {
        return sexo;
    }

    @Override
    public String toString() {
        return "[" + nome + "," + sexo + "]";
    }
}
