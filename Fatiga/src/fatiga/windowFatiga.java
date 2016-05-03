package fatiga;

import java.awt.FileDialog;
import java.io.File;

public class windowFatiga extends javax.swing.JFrame {

    public windowFatiga() {
        initComponents();
        setLocationRelativeTo(null);

    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        menu_option = new javax.swing.JPanel();
        load = new javax.swing.JButton();
        btn_rcc = new javax.swing.JButton();
        btn_slf = new javax.swing.JButton();
        btn_reset = new javax.swing.JButton();
        btn_exit = new javax.swing.JButton();
        main_contain = new javax.swing.JPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        load.setText("Load");
        load.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                loadActionPerformed(evt);
            }
        });

        btn_rcc.setText("RCC Analisys");

        btn_slf.setText("SLF Analysis");

        btn_reset.setText("Reset");

        btn_exit.setText("Exit");
        btn_exit.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_exitActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout menu_optionLayout = new javax.swing.GroupLayout(menu_option);
        menu_option.setLayout(menu_optionLayout);
        menu_optionLayout.setHorizontalGroup(
            menu_optionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(menu_optionLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(load, javax.swing.GroupLayout.PREFERRED_SIZE, 127, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(btn_rcc, javax.swing.GroupLayout.PREFERRED_SIZE, 139, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(btn_slf, javax.swing.GroupLayout.PREFERRED_SIZE, 169, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(btn_reset, javax.swing.GroupLayout.PREFERRED_SIZE, 156, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(btn_exit, javax.swing.GroupLayout.PREFERRED_SIZE, 98, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(54, Short.MAX_VALUE))
        );
        menu_optionLayout.setVerticalGroup(
            menu_optionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, menu_optionLayout.createSequentialGroup()
                .addContainerGap(9, Short.MAX_VALUE)
                .addGroup(menu_optionLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(load)
                    .addComponent(btn_rcc)
                    .addComponent(btn_slf)
                    .addComponent(btn_reset)
                    .addComponent(btn_exit))
                .addContainerGap())
        );

        javax.swing.GroupLayout main_containLayout = new javax.swing.GroupLayout(main_contain);
        main_contain.setLayout(main_containLayout);
        main_containLayout.setHorizontalGroup(
            main_containLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        main_containLayout.setVerticalGroup(
            main_containLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 366, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(menu_option, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(main_contain, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(menu_option, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(main_contain, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btn_exitActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_exitActionPerformed
        // TODO add your handling code here:

        System.exit(0);
    }//GEN-LAST:event_btn_exitActionPerformed

    private void loadActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_loadActionPerformed

        final FileDialog fileDialog = new FileDialog(this, "Select file");

        try {
            fileDialog.setVisible(true);
            File archivo[] = fileDialog.getFiles();
            System.out.println(archivo[0].getAbsolutePath());
            FatigaManager.getInstance().setArchivo_inicial(archivo[0]);
            FatigaManager.getInstance().fillDatos();
        } catch (Exception e) {
            System.out.println(e.toString());
        }


    }//GEN-LAST:event_loadActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {

        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(windowFatiga.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(windowFatiga.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(windowFatiga.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(windowFatiga.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new windowFatiga().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btn_exit;
    private javax.swing.JButton btn_rcc;
    private javax.swing.JButton btn_reset;
    private javax.swing.JButton btn_slf;
    private javax.swing.JButton load;
    private javax.swing.JPanel main_contain;
    private javax.swing.JPanel menu_option;
    // End of variables declaration//GEN-END:variables
}
