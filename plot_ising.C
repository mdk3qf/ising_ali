/*
 * plot_ising.C
 * ============
 * ROOT script to plot magnetization, energy, and specific heat
 * vs temperature from ising2d_vs_T.dat
 * 
 * Usage: root -l plot_ising.C
 */

void plot_ising() {
    
    // Read data from file
    const char* filename = "ising2d_vs_T.dat";
    
    // Create TGraph objects for each quantity
    TGraph *gr_mag = new TGraph(filename, "%lg %lg");
    TGraph *gr_energy = new TGraph(filename, "%lg %*lg %lg");
    TGraph *gr_heat = new TGraph(filename, "%lg %*lg %*lg %lg");
    
    // Create canvas
    TCanvas *c1 = new TCanvas("c1", "Ising Model Results", 800, 600);
    
    // Set up for multi-page PDF
    c1->Print("ising.pdf[");  // Open PDF file
    
    // ========== Plot 1: Magnetization vs T ==========
    c1->Clear();
    gr_mag->SetTitle("Magnetization vs Temperature;T;Magnetization");
    gr_mag->SetMarkerStyle(20);
    gr_mag->SetMarkerSize(0.8);
    gr_mag->SetMarkerColor(kBlue);
    gr_mag->SetLineColor(kBlue);
    gr_mag->SetLineWidth(2);
    gr_mag->Draw("APL");
    
    // Add grid
    c1->SetGrid();
    
    c1->Print("ising.pdf");  // Add this page to PDF
    
    // ========== Plot 2: Energy vs T ==========
    c1->Clear();
    gr_energy->SetTitle("Energy vs Temperature;T;Energy per spin");
    gr_energy->SetMarkerStyle(20);
    gr_energy->SetMarkerSize(0.8);
    gr_energy->SetMarkerColor(kRed);
    gr_energy->SetLineColor(kRed);
    gr_energy->SetLineWidth(2);
    gr_energy->Draw("APL");
    
    c1->SetGrid();    
    c1->Print("ising.pdf");  // Add this page to PDF
    
    // ========== Plot 3: Specific Heat vs T ==========
    c1->Clear();
    gr_heat->SetTitle("Specific Heat vs Temperature;T;Specific heat per spin");
    gr_heat->SetMarkerStyle(20);
    gr_heat->SetMarkerSize(0.8);
    gr_heat->SetMarkerColor(kGreen+2);
    gr_heat->SetLineColor(kGreen+2);
    gr_heat->SetLineWidth(2);
    gr_heat->Draw("APL");
    
    c1->SetGrid();
    
   // Find temperature at maximum specific heat
    int npoints = gr_heat->GetN();
    double *xdata = gr_heat->GetX();
    double *ydata = gr_heat->GetY();
    
    double max_C = ydata[0];
    double T_at_max = xdata[0];
    for (int i = 1; i < npoints; i++) {
        if (ydata[i] > max_C) {
            max_C = ydata[i];
            T_at_max = xdata[i];
        }
    }
    
    // Draw vertical line at maximum
    TLine *line = new TLine(T_at_max, gr_heat->GetYaxis()->GetXmin(), 
                            T_at_max, gr_heat->GetYaxis()->GetXmax());
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line->Draw();
    
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.03);
    char label[100];
    sprintf(label, "T_{c} #approx %.2f", T_at_max);
    latex->DrawLatex(T_at_max + 0.2, gr_heat->GetYaxis()->GetXmax()*0.9, label);
        
    c1->Print("ising.pdf");  // Add this page to PDF
    
    // Close PDF file
    c1->Print("ising.pdf]");

    cout << "Critical temperature of Maximum C approximately " << T_at_max << endl;
    cout << "Plots saved to ising.pdf" << endl;
    
    // Clean up
    delete gr_mag;
    delete gr_energy;
    delete gr_heat;
    delete c1;

    gApplication->Terminate();
}