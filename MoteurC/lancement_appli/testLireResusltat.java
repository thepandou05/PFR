import java.util.ArrayList;
public class testLireResusltat {

    public static void main(String[] args) {
       LireResultat lireresult = new LireResultat();
       lireresult.type="rechercheMot";
       lireresult.pontJavaC="pontJavaC.txt";
    //    ArrayList<ELLEMENT> listeElement = new ArrayList<>();
    //    listeElement=lireresult.lireChemin("texte");
    //    for( ELLEMENT lig : listeElement)
    //    {
    //        System.out.println(lig);
    //    }
    lireresult.lireResultatFinale(lireresult.type);

      
    }
}