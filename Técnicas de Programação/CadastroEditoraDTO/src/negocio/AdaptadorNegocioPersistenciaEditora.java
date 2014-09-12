package negocio;

import java.util.ArrayList;
import java.util.List;
import persistencia.EditoraDAO;
import persistencia.EditoraDTO;

/**
 *
 * @author Júlio
 */
public class AdaptadorNegocioPersistenciaEditora {
    private EditoraDAO dao;
    
    public AdaptadorNegocioPersistenciaEditora(EditoraDAO dao){
        this.dao = dao;
    }
    
    public List<Editora> buscarTodos() throws Exception{
        List<EditoraDTO> original = dao.buscarTodos();
        List<Editora> transformado = new ArrayList<>();
        for(EditoraDTO ed : original){
            transformado.add(transformardeDTO(ed));
        }
        return transformado;
    }
    
    public void inserir(Editora editora) throws Exception{
        EditoraDTO dto = transformarparaDTO(editora);
        dao.inserir(dto);
    }
    
    private Editora transformardeDTO(EditoraDTO dto){
        return new Editora(dto.getCodigo(), dto.getNome());
    }
    
    private EditoraDTO transformarparaDTO(Editora ed){
        EditoraDTO dto = new EditoraDTO();
        dto.setCodigo(ed.getCodigo());
        dto.setNome(ed.getNome());
        return dto;
    }
}
