using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HBaethgeA2_1LL
{
    public partial class frmA2_1LL : Form
    {
        LinkedList<double> numbers = new LinkedList<double>();

        public frmA2_1LL()
        {
            InitializeComponent();
        }

        private void frmA2_1LL_Load(object sender, EventArgs e)
        {

        }

        private void btnGetItems_Click(object sender, EventArgs e)
        {
            double[] random = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
            numbers = new LinkedList<double>(random);

            foreach(double n in numbers)
            {
                lbxDisplay.Items.Add(n);
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            double total = 0;
            foreach (double n in numbers)
            {
                total += n;
            }
            lbxDisplay.Items.Add("Total of numbers in list is: " + total);
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            if(numbers.Remove(3.3))
            {
                foreach (double n in numbers)
                {
                    lbxDisplay.Items.Add(n);
                }
                lbxDisplay.Items.Add("Removed 3.3 from list.");
            }
            else
            {
                lbxDisplay.Items.Add("Number not found in list.");
            }
        }

        private void btnAverage_Click(object sender, EventArgs e)
        {
            double total = 0, count = 0;
            foreach (double n in numbers)
            {
                total += n;
                count++;
            }
            total /= count;
            lbxDisplay.Items.Add("Average of numbers in list is: " + total);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            lbxDisplay.Items.Clear();
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
