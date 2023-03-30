package Controle;

import Boundary.BoundaryErreur;
import Entite.Affichage;
import Entite.LireResultat;
import Entite.ListCheminFichier;
import Entite.ReadWriteFichier;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class ControlMenuTexte {
    ControlLancerExecutable controlLancerExecutable;
    ControlLireResultat controlLireResultat;
    public ControlMenuTexte(ControlLancerExecutable controlLancerExecutable,ControlLireResultat controlLireResultat) {
        this.controlLancerExecutable = controlLancerExecutable ;
        this.controlLireResultat=controlLireResultat;
    }
    public Map<String, Integer> comparaisonTexte(String cheminFichierRecherche) {
        Map<String, Integer> resultatFinale = new HashMap<>();
        ReadWriteFichier.writeOn(ListCheminFichier.cheminPontJC, "comparaisonTexte(" + cheminFichierRecherche + ")");
        controlLancerExecutable.lancerOut();
        Affichage.setRequete(cheminFichierRecherche);
        return resultatFinale=controlLireResultat.affichage("texte",null,null);
    }

    public Map<String, Integer> rechercheMot(ArrayList<String> motsPlusAuMoins ) {
        Map<String, Integer> resultatFinale = new HashMap<>();
        ArrayList<String> pont = new ArrayList<>();
        ArrayList<String> recup = new ArrayList<>();
        int repere=0;
        for (int i = 0; i < motsPlusAuMoins.size(); i++) {
            if (motsPlusAuMoins.get(i).contains("+")) {
                ReadWriteFichier.writeOn(ListCheminFichier.cheminPontJC,"rechercheMot(" + motsPlusAuMoins.get(i).replace("+", "") + ")");
                controlLancerExecutable.lancerOut();
                if (pont.size() == 0 && repere == 0) {
                    pont = LireResultat.lirePontComplexe();
                    repere = 1;
                    //System.out.println("pont debut" + pont.toString());

                } else {

                    recup = LireResultat.lirePontComplexe();
                    //System.out.println("recup +" + recup.toString());
                    pont.retainAll(recup);
                    //System.out.println("pont intersection" + pont.toString());
                }
            }
        }

        for (int k = 0; k < motsPlusAuMoins.size(); k++) {
            if (motsPlusAuMoins.get(k).contains("-")) {
                ReadWriteFichier.writeOn(ListCheminFichier.cheminPontJC,"rechercheMot(" + motsPlusAuMoins.get(k).replace("-", "") + ")");
                controlLancerExecutable.lancerOut();
                recup = LireResultat.lirePontComplexe();
                pont.removeAll(recup);
            }
        }
        Affichage.setRequete(motsPlusAuMoins.toString()) ;
        return resultatFinale=controlLireResultat.affichage("requeteComplexe",pont,null);
    }




}
