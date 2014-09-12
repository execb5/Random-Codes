package negocio;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Livro {
    private int codigo;
    private String titulo;
    private int ano;
    private Editora editora;
    private List<Autor> autores;

    public Livro(int codigo, String titulo, int ano, Editora editora, Autor autor){
        this.codigo = codigo;
        this.titulo = titulo;
        this.ano = ano;
        this.editora = editora;
        autores = new ArrayList<>();
        autores.add(autor);
    }
    
    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public int getCodigo() {
        return codigo;
    }

    public Editora getEditora() {
        return editora;
    }

    public void setEditora(Editora editora) {
        this.editora = editora;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public List<Autor> getAutores() {
        return Collections.unmodifiableList(autores);
    }
    
    public boolean addAutor(Autor autor){
        for(Autor a : autores) {
            if(a.getCodigo() == autor.getCodigo()) {
                return true;
            }
        }
        return autores.add(autor);
    }

    @Override
    public String toString() {
        String s = codigo + "," + titulo + "," + ano + ",[" + editora +"]";
        if(!autores.isEmpty()){
            StringBuilder completo = new StringBuilder(s);
            for(Autor a : autores) {
                completo.append(",[");
                completo.append(a.toString());
                completo.append("]");
            }
            s = completo.toString();
        }
        return s;
    }
}