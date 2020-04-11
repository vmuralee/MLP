void Liklihood()
{
//=========Macro generated from canvas: c1/
//=========  (Sat Apr 11 16:43:14 2020) by ROOT version 6.20/00
   TCanvas *c1 = new TCanvas("c1", "",93,102,700,600);
   c1->Range(-1.25,-0.07430101,1.25,0.668709);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hMLPSig__1 = new TH1D("hMLPSig__1","BDT",100,-10,10);
   hMLPSig__1->SetBinContent(46,0.0006903693);
   hMLPSig__1->SetBinContent(47,0.004142216);
   hMLPSig__1->SetBinContent(48,0.009665171);
   hMLPSig__1->SetBinContent(49,0.05799103);
   hMLPSig__1->SetBinContent(50,0.04694512);
   hMLPSig__1->SetBinContent(51,0.5661029);
   hMLPSig__1->SetBinContent(52,0.3144632);
   hMLPSig__1->SetBinError(46,0.0004881648);
   hMLPSig__1->SetBinError(47,0.001195755);
   hMLPSig__1->SetBinError(48,0.001826546);
   hMLPSig__1->SetBinError(49,0.004474105);
   hMLPSig__1->SetBinError(50,0.00402551);
   hMLPSig__1->SetBinError(51,0.01397891);
   hMLPSig__1->SetBinError(52,0.01041863);
   hMLPSig__1->SetEntries(2897);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("hMLPSig");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 2897   ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.1205");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.1736");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(0);
   //ptstats->Draw();
   hMLPSig__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hMLPSig__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   hMLPSig__1->SetFillColor(ci);
   hMLPSig__1->SetFillStyle(3001);

   ci = TColor::GetColor("#ff0000");
   hMLPSig__1->SetLineColor(ci);
   hMLPSig__1->GetXaxis()->SetRange(46,55);
   hMLPSig__1->GetXaxis()->SetRangeUser(-1,0.4);
   hMLPSig__1->GetXaxis()->SetLabelFont(42);
   hMLPSig__1->GetXaxis()->SetTitleOffset(1);
   hMLPSig__1->GetXaxis()->SetTitleFont(42);
   hMLPSig__1->GetXaxis()->SetTitle("BDT Score");
   hMLPSig__1->GetYaxis()->SetLabelFont(42);
   hMLPSig__1->GetYaxis()->SetTitleFont(42);
   hMLPSig__1->GetYaxis()->SetRangeUser(0,1);
   hMLPSig__1->GetZaxis()->SetLabelFont(42);
   hMLPSig__1->GetZaxis()->SetTitleOffset(1);
   hMLPSig__1->GetZaxis()->SetTitleFont(42);
   hMLPSig__1->Draw("histo");
   
   TPaveText *pt = new TPaveText(0.3574699,0.9343684,0.6425301,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("BDT test statitics");
   pt->Draw();
   
   TH1D *hMLPBkg__2 = new TH1D("hMLPBkg__2","MLP, background",100,-10,10);
   hMLPBkg__2->SetBinContent(46,0.7200512);
   hMLPBkg__2->SetBinContent(47,0.0278524);
   hMLPBkg__2->SetBinContent(48,0.05457037);
   hMLPBkg__2->SetBinContent(49,0.09866773);
   hMLPBkg__2->SetBinContent(50,0.02370494);
   hMLPBkg__2->SetBinContent(51,0.04527716);
   hMLPBkg__2->SetBinContent(52,0.02987621);
   hMLPBkg__2->SetBinError(46,0.002556316);
   hMLPBkg__2->SetBinError(47,0.000502764);
   hMLPBkg__2->SetBinError(48,0.0007037385);
   hMLPBkg__2->SetBinError(49,0.0009462817);
   hMLPBkg__2->SetBinError(50,0.000463823);
   hMLPBkg__2->SetBinError(51,0.0006410213);
   hMLPBkg__2->SetBinError(52,0.0005207096);
   hMLPBkg__2->SetEntries(110188);
   
   ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   ptstats_LaTex = ptstats->AddText("hMLPBkg");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 110188 ");
   ptstats_LaTex = ptstats->AddText("Mean  = -0.7133");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.3376");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(0);
   //ptstats->Draw();
   hMLPBkg__2->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hMLPBkg__2);

   ci = TColor::GetColor("#0000ff");
   hMLPBkg__2->SetFillColor(ci);
   hMLPBkg__2->SetFillStyle(3001);

   ci = TColor::GetColor("#000099");
   hMLPBkg__2->SetLineColor(ci);
   hMLPBkg__2->GetXaxis()->SetRange(46,55);
   hMLPBkg__2->GetXaxis()->SetLabelFont(42);
   hMLPBkg__2->GetXaxis()->SetTitleOffset(1);
   hMLPBkg__2->GetXaxis()->SetTitleFont(42);
   hMLPBkg__2->GetYaxis()->SetLabelFont(42);
   hMLPBkg__2->GetYaxis()->SetTitleFont(42);
   hMLPBkg__2->GetZaxis()->SetLabelFont(42);
   hMLPBkg__2->GetZaxis()->SetTitleOffset(1);
   hMLPBkg__2->GetZaxis()->SetTitleFont(42);
   hMLPBkg__2->Draw("histosame");

   TLegend* leg = new TLegend(0.78,0.775,0.98,0.935,"");
   leg->AddEntry(hMLPSig__1,"quark Jet","F");
   leg->AddEntry(hMLPBkg__2,"gluon Jet","F");
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
