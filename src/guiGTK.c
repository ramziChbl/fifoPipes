#include <gtk/gtk.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "trace.h"

void affichtable(operation t[], int n);


//------------ Widgets GTK -------------------------------------
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
//--------------------------------------------------------------

static void somme (GtkWidget *widget, gpointer data)
{
    int a = atoi(gtk_entry_get_text(GTK_ENTRY(op1Entry)));
    int b = atoi(gtk_entry_get_text ((GTK_ENTRY(op2Entry))));

    remove("guiCalcul.fifo");
    remove("calcul-gui.fifo");
    remove("calcul-trace.fifo");

    char res[20];
    char chaineAEcrire[20];
    int entreeTube;
    char nomTube[20] = "guiCalcul.fifo";

    sprintf(chaineAEcrire, "1 %d %d",a,b);

    mkfifo(nomTube, 0644);
    entreeTube = open(nomTube, O_WRONLY);
 
    write(entreeTube, chaineAEcrire, 20);


    // Lecture du resultat
    int sortieTube;
    char nomCalculGuiTube[20] = "calcul-gui.fifo";
    char resultatALire[20];

    while((sortieTube = open ("calcul-gui.fifo", O_RDONLY)) == -1)
    {
        usleep(20000);
    }

    read(sortieTube, res, 20);
    gtk_label_set_text (GTK_LABEL(resultLabel), res);
    remove(nomCalculGuiTube);
}


static void produit (GtkWidget *widget, gpointer data)
{
      int a = atoi(gtk_entry_get_text(GTK_ENTRY(op1Entry)));
    int b = atoi(gtk_entry_get_text ((GTK_ENTRY(op2Entry))));

    remove("guiCalcul.fifo");
    remove("calcul-gui.fifo");
    remove("calcul-trace.fifo");

    char res[20];
    char chaineAEcrire[20];
    int entreeTube;
    char nomTube[20] = "guiCalcul.fifo";


    sprintf(chaineAEcrire, "2 %d %d",a,b);

    mkfifo(nomTube, 0644);
    entreeTube = open(nomTube, O_WRONLY);
 
    write(entreeTube, chaineAEcrire, 20);


    // Lecture du resultat
    int sortieTube;
    char nomCalculGuiTube[20] = "calcul-gui.fifo";
    char resultatALire[20];

    while((sortieTube = open ("calcul-gui.fifo", O_RDONLY)) == -1)
    {
        usleep(20000);
    }

    read(sortieTube, res, 20);
    gtk_label_set_text (GTK_LABEL(resultLabel), res);
    remove(nomCalculGuiTube);
}


static void factorielle (GtkWidget *widget, gpointer data)
{
      int a = atoi(gtk_entry_get_text(GTK_ENTRY(op1Entry)));
    int b = atoi(gtk_entry_get_text ((GTK_ENTRY(op2Entry))));

    remove("guiCalcul.fifo");
    remove("calcul-gui.fifo");
    remove("calcul-trace.fifo");

    char res[20];
    char chaineAEcrire[20];
    int entreeTube;
    char nomTube[20] = "guiCalcul.fifo";


    sprintf(chaineAEcrire, "3 %d",a);

    mkfifo(nomTube, 0644);
    entreeTube = open(nomTube, O_WRONLY);
 
    write(entreeTube, chaineAEcrire, 20);

    // Lecture du resultat
    int sortieTube;
    char nomCalculGuiTube[20] = "calcul-gui.fifo";
    char resultatALire[20];

    while((sortieTube = open ("calcul-gui.fifo", O_RDONLY)) == -1)
    {
        usleep(20000);
    }

    read(sortieTube, res, 20);
    gtk_label_set_text (GTK_LABEL(resultLabel), res);
    remove(nomCalculGuiTube);
}


static void trace (GtkWidget *widget, gpointer data)
{
  g_print ("trace\n");
    FILE *ftrack;
    operation ops[100];
    
    ftrack = fopen("track.trc","r+b");
    if (ftrack == NULL)
        return;

    int nops = fread(ops,sizeof(operation),100,ftrack);
    fclose(ftrack);
    affichtable(ops, nops);
}


static void activate (GtkApplication *app, gpointer user_data)
{
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "TP3 - Pipes and Filters");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 280);


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
    factButton = gtk_button_new_with_label ("Factorielle");
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

void affichtable(operation t[], int n){
    printf("operation ! operande G ! operande D ! resultat !\n");
    printf("------------------------------------------------\n"); 

    for (int i=0; i<n; i++)
    { 
        printf(" %5d    ! %6d     ! %6d     !  %6ld  !\n",t[i].o, t[i].g, t[i].d, t[i].r);
        printf("----------!------------!------------!----------!\n");

    }   

}

