module nrainhas.nrainhas_frontend {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires java.desktop;
    requires jdk.incubator.vector;

    opens nrainhas.nrainhas_frontend.controller to javafx.fxml;

    opens nrainhas.nrainhas_frontend to javafx.fxml;
    exports nrainhas.nrainhas_frontend;
    exports nrainhas.nrainhas_frontend.controller;
}