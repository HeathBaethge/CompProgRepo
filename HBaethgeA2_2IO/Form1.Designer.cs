namespace HBaethgeA2_2IO
{
    partial class frmAdvancedIO
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lbxSales = new System.Windows.Forms.ListBox();
            this.btnSales = new System.Windows.Forms.Button();
            this.lbxCalculations = new System.Windows.Forms.ListBox();
            this.lblMouseClickPrompt = new System.Windows.Forms.Label();
            this.lblMouseClicks = new System.Windows.Forms.Label();
            this.btnExit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbxSales
            // 
            this.lbxSales.FormattingEnabled = true;
            this.lbxSales.Location = new System.Drawing.Point(18, 58);
            this.lbxSales.Name = "lbxSales";
            this.lbxSales.Size = new System.Drawing.Size(178, 186);
            this.lbxSales.TabIndex = 0;
            // 
            // btnSales
            // 
            this.btnSales.Location = new System.Drawing.Point(202, 143);
            this.btnSales.Name = "btnSales";
            this.btnSales.Size = new System.Drawing.Size(75, 23);
            this.btnSales.TabIndex = 1;
            this.btnSales.Text = "&Sales";
            this.btnSales.UseVisualStyleBackColor = true;
            this.btnSales.Click += new System.EventHandler(this.btnSales_Click);
            // 
            // lbxCalculations
            // 
            this.lbxCalculations.FormattingEnabled = true;
            this.lbxCalculations.Location = new System.Drawing.Point(283, 58);
            this.lbxCalculations.Name = "lbxCalculations";
            this.lbxCalculations.Size = new System.Drawing.Size(178, 186);
            this.lbxCalculations.TabIndex = 2;
            // 
            // lblMouseClickPrompt
            // 
            this.lblMouseClickPrompt.AutoSize = true;
            this.lblMouseClickPrompt.Location = new System.Drawing.Point(182, 271);
            this.lblMouseClickPrompt.Name = "lblMouseClickPrompt";
            this.lblMouseClickPrompt.Size = new System.Drawing.Size(113, 13);
            this.lblMouseClickPrompt.TabIndex = 3;
            this.lblMouseClickPrompt.Text = "Mouse was clicked at:";
            // 
            // lblMouseClicks
            // 
            this.lblMouseClicks.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblMouseClicks.Location = new System.Drawing.Point(185, 284);
            this.lblMouseClicks.Name = "lblMouseClicks";
            this.lblMouseClicks.Size = new System.Drawing.Size(110, 23);
            this.lblMouseClicks.TabIndex = 4;
            this.lblMouseClicks.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(202, 365);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 23);
            this.btnExit.TabIndex = 5;
            this.btnExit.Text = "E&xit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // frmAdvancedIO
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 461);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.lblMouseClicks);
            this.Controls.Add(this.lblMouseClickPrompt);
            this.Controls.Add(this.lbxCalculations);
            this.Controls.Add(this.btnSales);
            this.Controls.Add(this.lbxSales);
            this.Name = "frmAdvancedIO";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Advanced Input and Output";
            this.Load += new System.EventHandler(this.frmAdvancedIO_Load);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.mouse_Click);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lbxSales;
        private System.Windows.Forms.Button btnSales;
        private System.Windows.Forms.ListBox lbxCalculations;
        private System.Windows.Forms.Label lblMouseClickPrompt;
        private System.Windows.Forms.Label lblMouseClicks;
        private System.Windows.Forms.Button btnExit;
    }
}

