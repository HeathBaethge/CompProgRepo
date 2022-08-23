using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HBaethgeA2_4SS
{
    public partial class frmMain : Form
    {
        double num1, num2;

        public frmMain()
        {
            InitializeComponent();
        }        

        private void btnAdd_Click(object sender, EventArgs e)
        {
            Double.TryParse(tbxNum1.Text, out num1);
            Double.TryParse(tbxNum2.Text, out num2);
            lblOperation.Text = "+";
            lblOutput.Text = (num1 + num2).ToString();
        }

        private void btnSubtract_Click(object sender, EventArgs e)
        {
            Double.TryParse(tbxNum1.Text, out num1);
            Double.TryParse(tbxNum2.Text, out num2);
            lblOperation.Text = "-";
            lblOutput.Text = (num1 - num2).ToString();
        }
        private void btnMultiply_Click(object sender, EventArgs e)
        {
            Double.TryParse(tbxNum1.Text, out num1);
            Double.TryParse(tbxNum2.Text, out num2); 
            lblOperation.Text = "*";
            lblOutput.Text = (num1 * num2).ToString();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            tbxNum1.Text = "";
            tbxNum2.Text = "";
            lblOperation.Text = "";
            lblOutput.Text = "";
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnDivide_Click(object sender, EventArgs e)
        {
            Double.TryParse(tbxNum1.Text, out num1);
            Double.TryParse(tbxNum2.Text, out num2);
            if(num1 == 0)
            {
                MessageBox.Show("Can't divide 0.  Please enter another number.");
                tbxNum1.Focus();
            }
            else
            {
                lblOperation.Text = "/";
                lblOutput.Text = (num1 / num2).ToString();
            }            
        }
    }
}
