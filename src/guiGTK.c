#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *window;
GtkWidget *button;
GtkWidget *button_box;
GtkWidget *main_box; // Vertical
GtkWidget *operand_box; // Horizontal
GtkWidget *operation_box; //Horizontal
GtkWidget *quitterTrace_box; // Horizontal

GtkWidget *headerLabel;
GtkWidget *op1Entry, *op2Entry;
GtkWidget *resultTitleLabel, *resultLabel;

GtkWidget *sumButton, *prodButton, *factButton;
GtkWidget *quitButton, *traceButton;

static void print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}

static void somme (GtkWidget *widget, gpointer data)
{
  g_print ("somme\n");
  int n1 = atoi(gtk_entry_get_text(GTK_ENTRY(op1Entry))), n2 = atoi(gtk_entry_get_text ((GTK_ENTRY(op1Entry))));
  char res[10];
  sprintf(res, "%d", n1 + n2);
  gtk_label_set_text (GTK_LABEL(resultLabel), res);
}


static void produit (GtkWidget *widget, gpointer data)
{
  g_print ("produit\n");
}


static void factorielle (GtkWidget *widget, gpointer data)
{
  g_print ("factorielle\n");
}


static void trace (GtkWidget *widget, gpointer data)
{
  g_print ("trace\n");
}


static void activate (GtkApplication *app, gpointer user_data)
{
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);


    main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    operand_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    operation_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    quitterTrace_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);

    headerLabel = gtk_label_new("<span size=\"xx-large\"><b>Calculatrice avec Pipes and Filters</b></span>");
    gtk_label_set_use_markup(GTK_LABEL(headerLabel), TRUE); // On dit que l'on utilise les balises pango
    gtk_widget_set_margin_top (headerLabel, 20);
    gtk_widget_set_margin_bottom (headerLabel, 20);
    gtk_widget_set_margin_start (headerLabel, 20);
    gtk_widget_set_margin_end (headerLabel, 20);

    resultTitleLabel = gtk_label_new("<b>Resultat</b>");
    gtk_label_set_use_markup(GTK_LABEL(resultTitleLabel), TRUE); // On dit que l'on utilise les balises pango
    gtk_widget_set_margin_top (resultTitleLabel, 20);
    resultLabel = gtk_label_new("...");


    op1Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(op1Entry), "Nombre 1");
    gtk_widget_set_margin_top (op1Entry, 20);
    gtk_widget_set_margin_bottom (op1Entry, 20);
    gtk_widget_set_margin_start (op1Entry, 20);
    gtk_widget_set_margin_end (op1Entry, 20);
    op2Entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(op2Entry), "Nombre 2");
    gtk_widget_set_margin_top (op2Entry, 20);
    gtk_widget_set_margin_bottom (op2Entry, 20);
    gtk_widget_set_margin_start (op2Entry, 20);
    gtk_widget_set_margin_end (op2Entry, 20);

    sumButton = gtk_button_new_with_label ("Somme");
    prodButton = gtk_button_new_with_label ("Produit");
    factButton = gtk_button_new_with_label ("Fctorielle");
    traceButton = gtk_button_new_with_label ("Trace");
    quitButton = gtk_button_new_with_label ("Quitter");


    // ---------- Button Actions ------------------------------------------------------
    g_signal_connect (sumButton, "clicked", G_CALLBACK (somme), NULL);
    g_signal_connect (prodButton, "clicked", G_CALLBACK (produit), NULL);
    g_signal_connect (factButton, "clicked", G_CALLBACK (factorielle), NULL);
    g_signal_connect_swapped (quitButton, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    g_signal_connect (traceButton, "clicked", G_CALLBACK (trace), NULL);



    gtk_container_add (GTK_CONTAINER (operation_box), sumButton);
    gtk_container_add (GTK_CONTAINER (operation_box), prodButton);
    gtk_container_add (GTK_CONTAINER (operation_box), factButton);

    gtk_button_box_set_layout (GTK_BUTTON_BOX(operation_box), GTK_BUTTONBOX_CENTER);
    

    gtk_container_add (GTK_CONTAINER (operand_box), op1Entry);
    gtk_container_add (GTK_CONTAINER (operand_box), op2Entry);
    gtk_widget_set_halign (operand_box,GTK_ALIGN_CENTER);

    gtk_container_add (GTK_CONTAINER (quitterTrace_box), traceButton);
    gtk_container_add (GTK_CONTAINER (quitterTrace_box), quitButton);

    gtk_container_add (GTK_CONTAINER (main_box), headerLabel);
    gtk_container_add (GTK_CONTAINER (main_box), operand_box);
    gtk_container_add (GTK_CONTAINER (main_box), operation_box);
    gtk_container_add (GTK_CONTAINER (main_box), resultTitleLabel);
    gtk_container_add (GTK_CONTAINER (main_box), resultLabel);

    gtk_container_add (GTK_CONTAINER (main_box), quitterTrace_box);

    gtk_container_add (GTK_CONTAINER (window), main_box);

  gtk_widget_show_all (window);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

