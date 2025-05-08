package nrainhas.nrainhas_frontend.model;

import java.util.ArrayList;
import java.util.List;

public class Tabuleiro {
    private int tamanho;
    private List<Rainha> rainhas;

    public Tabuleiro(int tamanho) {
        this.tamanho = tamanho;
        this.rainhas = new ArrayList<>();
    }

    public int getTamanho() {
        return tamanho;
    }

    public void setTamanho(int tamanho) {
        this.tamanho = tamanho;
    }

    public List<Rainha> getRainhas() {
        return rainhas;
    }

    public void setRainhas(List<Rainha> rainhas) {
        this.rainhas = rainhas;
    }

    public void adicionarRainha(Rainha rainha) {
        rainhas.add(rainha);
    }
}
