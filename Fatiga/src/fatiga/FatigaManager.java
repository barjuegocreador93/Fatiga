/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fatiga;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;

/**
 *
 * @author acoulson
 */
public class FatigaManager {

    private static FatigaManager instance = null;

    private File archivo_inicial;

    private ArrayList<Double> datos = new ArrayList();

    protected FatigaManager() {
    }

    public static FatigaManager getInstance() {

        if (instance == null) {
            instance = new FatigaManager();
        }
        return instance;
    }

    public void fillDatos() {

        try (BufferedReader br = new BufferedReader(new FileReader(this.archivo_inicial.getAbsolutePath()))) {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append(System.lineSeparator());
                datos.add(Double.parseDouble(line));
                line = br.readLine();
                
                
            }
            
            System.out.println(datos.get(datos.size()-1));

        } catch (Exception e) {
            System.out.println(e.toString());
        }

    }

    public File getArchivo_inicial() {
        return archivo_inicial;
    }

    public void setArchivo_inicial(File archivo_inicial) {
        this.archivo_inicial = archivo_inicial;
    }

}
