package nrainhas.nrainhas_frontend;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import nrainhas.nrainhas_frontend.controller.TelaPrincipalController;

import java.io.IOException;

public class MainApp extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/TelaPrincipal.fxml"));
        GridPane root = loader.load();

        TelaPrincipalController telaPrincipalController = loader.getController();
        telaPrincipalController.setStage(stage);

        stage.setTitle("N RAINHAS");
        Scene scene = new Scene(root);
        scene.getStylesheets().add(getClass().getResource("/TelaPrincipal.css").toExternalForm());

        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
