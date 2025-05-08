package nrainhas.nrainhas_frontend.controller;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.geometry.HPos;
import javafx.geometry.VPos;
import javafx.scene.Node;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.util.Duration;
import nrainhas.nrainhas_frontend.model.Rainha;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class RainhaController {

    private GridPane tabuleiroGrid;
    private int tamanhoTabuleiro;
    private List<Rainha> rainhas;
    private TelaPrincipalController telaPrincipalController;
    private Timeline timeline;
    private Random random;

    public RainhaController(GridPane tabuleiroGrid, int tamanhoTabuleiro, TelaPrincipalController telaPrincipalController){
        this.tabuleiroGrid = tabuleiroGrid;
        this.tamanhoTabuleiro = tamanhoTabuleiro;
        this.rainhas = new ArrayList<>();
        this.random = new Random();
        this.telaPrincipalController = telaPrincipalController;
    }

    public void inicializarRainhas(){
        rainhas.clear();

        for(int i = 0; i < tamanhoTabuleiro; i++) {
            Rainha rainha = new Rainha(i, gerarPosicaoAleatoria()); // Gera uma rainha por linha
            rainhas.add(rainha);
            adicionarRainhaVisual(rainha);
        }
    }

    private int gerarPosicaoAleatoria() {
        return random.nextInt(tamanhoTabuleiro);
    }

    private void adicionarRainhaVisual(Rainha rainha){
        Image rainhaImage = new Image(getClass().getResourceAsStream("/coroa.png"));
        ImageView rainhaView = new ImageView(rainhaImage);

        // Ajuste do tamanho da imagem
        rainhaView.setFitWidth(40); // Define a largura
        rainhaView.setFitHeight(40); // Define a altura
        rainhaView.setPreserveRatio(true); // Mantém a proporção da imagem

        //Circle celulaRainha = new Circle(20);
        //celulaRainha.setFill(Color.GREEN);

        tabuleiroGrid.add(rainhaView, rainha.getColuna(), rainha.getLinha());

        GridPane.setHalignment(rainhaView, HPos.CENTER);
        GridPane.setValignment(rainhaView, VPos.CENTER);
    }

    public void iniciarMovimento(int rodadas){
        if(timeline != null)
            timeline.stop();

        timeline = new Timeline(new KeyFrame(Duration.seconds(1), event -> moverRainhas()));
        timeline.setCycleCount(rodadas);
        telaPrincipalController.setMovimentoTimeline(timeline);
        timeline.play();
    }

    private void moverRainhas(){
        tabuleiroGrid.getChildren().clear(); // Limpa o tabuleiro para a proxima rodada

        // Atualiza as cores do tabuleiro
        telaPrincipalController.gerarTabuleiro();

        // Move cada rainha para uma nova posição aleatória
        for (Rainha rainha : rainhas) {
            // Atualize a posição da rainha diretamente
            rainha.setColuna(gerarPosicaoAleatoria());

            // Atualize visualmente sem recriar
            Node rainhaNode = obterRainhaVisual(rainha);
            GridPane.setColumnIndex(rainhaNode, rainha.getColuna());
            GridPane.setRowIndex(rainhaNode, rainha.getLinha());

            adicionarRainhaVisual(rainha);
        }
    }

    // Busque o Node correspondente à rainha no tabuleiroGrid
    private Node obterRainhaVisual(Rainha rainha) {
        return tabuleiroGrid.getChildren().stream()
                .filter(node -> GridPane.getRowIndex(node) == rainha.getLinha() &&
                        GridPane.getColumnIndex(node) == rainha.getColuna())
                .findFirst().orElse(null);
    }
}
