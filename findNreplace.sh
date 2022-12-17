#!/bin/bash

# list of names
OAname=(
ISO_BKG                      FEFABS                     P1_2Shell_MF_PMissShape_O
CA5                          FEFCXH                     P3_2Shell_MF_Norm_O
CC_norm_nubar                FEFCX                      P3_2Shell_MF_PMissShape_O
CC_norm_nu                   FEFINEL                    Pauli_Blocking_C_nubar
CC_MultiPi_norm_nubar        FEFQEH                     Pauli_Blocking_C_nu
CC_MultiPi_norm_nu           FEFQE                      Pauli_Blocking_O_nubar
MAQE                         Q2_norm_1                  Pauli_Blocking_O_nu
MARES                        Q2_norm_2                  PShell_MF_Norm_C
2p2h_Norm_C                  Q2_norm_3                  PShell_MF_PMissShape_C
2p2h_Norm_O                  RES_Eb_C_numubar           SRC_Norm_C
2p2h_Norm_Other              RES_Eb_C_numu              SRC_Norm_O
2p2h_shape_C_NN              RES_Eb_O_numubar           SShell_MF_Norm_C
2p2h_shape_C_np              RES_Eb_O_numu              SShell_MF_Norm_O
2p2h_shape_O_NN              Optical_Potential_C        SShell_MF_PMissShape_C
2p2h_shape_O_np              Optical_Potential_O        SShell_MF_PMissShape_O
PNNN_Shape                   P1_2Shell_MF_Norm_O        Nucleon_FSI
)

Kenjname=(
BgSclRES                     PionFSI_AbsProb            SF_P1_2Shell_MeanF_PMissShape_O
CA5RES                       PionFSI_CExHighMomProb     SF_P3_2Shell_MeanF_Norm_O
CC_DIS_norm_nubar            PionFSI_CExLowMomProb      SF_P3_2Shell_MeanF_PMissShape_O
CC_DIS_norm_nu               PionFSI_InelProb           SF_PBTwkDial_Hybrid_C12_nubar
CC_MultiPi_norm_nubar        PionFSI_QEHighMomProb      SF_PBTwkDial_Hybrid_C12_nu
CC_MultiPi_norm_nu           PionFSI_QELowMomProb       SF_PBTwkDial_Hybrid_O16_nubar
MaCCQE                       QETwk_HighQ2Weight_1       SF_PBTwkDial_Hybrid_O16_nu
MaRES                        QETwk_HighQ2Weight_2       SF_PShell_MeanF_Norm_C
MECTwkDial_Norm_C12          QETwk_HighQ2Weight_3       SF_PShell_MeanF_PMissShape_C
MECTwkDial_Norm_O16          RES_Eb_C_numubar           SF_SRC_Norm_C
MECTwkDial_Norm_Other        RES_Eb_C_numu              SF_SRC_Norm_O
MECTwkDial_PDDWeight_C12_NN  RES_Eb_O_numubar           SF_SShell_MeanF_Norm_C
MECTwkDial_PDDWeight_C12_np  RES_Eb_O_numu              SF_SShell_MeanF_Norm_O
MECTwkDial_PDDWeight_O16_NN  SF_OptPotTwkDial_C12       SF_SShell_MeanF_PMissShape_C
MECTwkDial_PDDWeight_O16_np  SF_OptPotTwkDial_O16       SF_SShell_MeanF_PMissShape_O
MECTwkDial_PNNN_Shape        SF_P1_2Shell_MeanF_Norm_O  TwkDial_FateNucleonFSI
)
# finds word in given file and replaces with words from list
i=0
for name in ${Kenjname[*]};
do
     sed -i 's/'$name'/'${OAname[i]}'/g' $1
     #echo 's/'$name'/'${OAname[i]}'/g' $1
    ((i++))
done
