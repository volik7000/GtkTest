#include <stdio.h>
#include <gtk/gtk.h>


GtkBuilder *builder;
GtkWidget *window;
//builder = gtk_builder_new();
//gtk_builder_add_from_file(builder, "calcular_imposto_de_renda.glade", NULL);
float calcular_inss(float salario, int dependentes)
{
   float A,B,C,D; //A-7,5  B-15   C-22,5   D-27,5
   float imposto=0;
   float valor_dependentes=189.59;
   float produto_dependentes = dependentes*valor_dependentes;

   A = 1100.01;
   B = 2203.49;
   C = 3305.23;
   D = 6433.58;
   if(salario < A) {
      imposto = (salario)*0.075;
   }
   else if(salario >= A && salario < B ) {
      imposto = A*0.075;
      imposto += (salario-A)*0.09;
   }
   else if(salario >= B && salario < C ) {
      imposto = A*0.075;
      imposto += (B-A)*0.09;
      imposto += (salario-B)*0.12;
   }
   else if(salario >= C  && salario < D ) {
      imposto = A*0.075;
      imposto += (B-A)*0.09;
      imposto += (C-B)*0.12;
      imposto += (salario-C)*0.14;
   }
   else {
      printf("Salario muito alto!\n");
      return 0;
   }
   return salario-produto_dependentes-imposto;
}
float calcular_irrf(float salario) {
   float aliquota=1,deducao=0;
   float IRRF=0;

   if(salario >= 1903.99 && salario <= 2826.65) {
      aliquota = 0.075;
      deducao = 142.80;
   }
   else if(salario >= 2826.66 && salario <= 3751.05) {
      aliquota = 0.15;
      deducao = 354.80;
   }
   else if(salario >= 3751.06 && salario <= 4664.68) {
      aliquota = 0.225;
      deducao = 636.13;
   }
   else {
      aliquota = 0.275;
      deducao = 869.36;
   }
   IRRF = ((salario*aliquota) - deducao);
//   printf("Salario: %.2f\nAliquota: %.2f\nDeducao: %.2f",salario,aliquota,deducao);
   return IRRF;
}
/////on_button_calcular_clicked
void on_button_calcular_clicked()
{
   GtkWidget *resultado;
   GtkWidget *salario;
   GtkWidget *spin_button;

   spin_button = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_spin_button_dependentes"));
   resultado = GTK_WIDGET(gtk_builder_get_object(builder, "gtklabel_resultado"));
   salario = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_entry_salario"));

   int dependentes = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));

   char buffer[32];
   float valor_salario = atof((char *)gtk_entry_get_text(GTK_ENTRY(salario))); //é possível transofrmar o "text" depois de obter por meio de get em char*(string), para deois transformar em inteiro com atoi()
   float calculo;// = calcular_inss(valor_salario,dependentes);
   if(!(calculo = calcular_inss(valor_salario,dependentes))) {
       gtk_label_set_text(GTK_LABEL(resultado), "Salario muito alto!");
    }else {
      calculo = calcular_irrf(calculo);
      calculo = calculo < 0 ? 0 : calculo;
      snprintf(buffer,sizeof(buffer), "%.2f", calculo);
      gtk_label_set_text(GTK_LABEL(resultado), buffer);
   }
//   gtk_widget_show(window);
}

void on_radiobutton_sim_toggled() {
//   GtkWidget *gtk_spin_button;
//   gtk_spin_button = GTK(gtk_builder_get_object(builder,"gtk_spin_button_dependentes"));
    GtkWidget *dependentes;
    dependentes = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_spin_button_dependentes"));
    gtk_widget_show(GTK_WIDGET(dependentes));

}
void on_radiobutton_nao_toggled() {
   GtkWidget *dependentes;
   dependentes = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_spin_button_dependentes"));
   gtk_widget_hide(GTK_WIDGET(dependentes));
}
void on_window_main_destroy()
{
   gtk_main_quit();
}
int main(int argc, char *argv[]) {
   //GtkApplication *app = gtk_application_new("org.gtkmm.example.Hello", G_APPLICATION_FAGS_NONE);
 //  GtkBuilder *builder;
 //  GtkWidget  *window;

   gtk_init(&argc, &argv);
   builder = gtk_builder_new();
   gtk_builder_add_from_file(builder, "calcular_imposto_de_renda.glade", NULL);


   window = GTK_WIDGET(gtk_builder_get_object(builder,"window_main"));
   gtk_builder_connect_signals(builder, NULL);

   gtk_widget_show(window);
   gtk_main();
   g_object_unref(builder);
   return 0;
}
