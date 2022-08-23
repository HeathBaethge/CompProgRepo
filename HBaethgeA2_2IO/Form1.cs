using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace HBaethgeA2_2IO
{
    public partial class frmAdvancedIO : Form
    {
        StreamReader stread = new StreamReader("sales.txt");
        StreamWriter stwrite = new StreamWriter("report.txt");
        double[] nums = new double[9];
        double total = 0, avg = 0;

        public frmAdvancedIO()
        {
            InitializeComponent();
        }

        private void mouse_Click(object sender, MouseEventArgs e)
        {
            lblMouseClicks.Text = (e.X + ", " + e.Y);
            if (e.X < 250 && e.Y < 250)
            {
                MessageBox.Show("You clicked in the Upper Left quadrant.");
            }
            if (e.X < 250 && e.Y > 250)
            {
                MessageBox.Show("You clicked in the Lower Left quadrant.");
            }
            if (e.X > 250 && e.Y < 250)
            {
                MessageBox.Show("You clicked in the Upper Right quadrant.");
            }
            if (e.X > 250 && e.Y > 250)
            {
                MessageBox.Show("You clicked in the Lower Right quadrant.");
            }           
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void frmAdvancedIO_Load(object sender, EventArgs e)
        {
            for(int i=0; i < nums.Length; i++)
            {
                nums[i] = double.Parse(stread.ReadLine());
                lbxSales.Items.Add(nums[i].ToString());
            }
        }

        private void btnSales_Click(object sender, EventArgs e)
        {
            Calculate(nums);
            Output();
        }

        public void Calculate(double[] nums)
        {
            Array.Sort(nums);
            
            for (int i = 0; i < nums.Length; i++)
            {
                total += nums[i];
            }
            avg = total/9;
        }

        public void Output()
        {
            lbxCalculations.Items.Add("Total of all values:");
            lbxCalculations.Items.Add(total);
            stwrite.WriteLine(total);
            lbxCalculations.Items.Add("Average of all values:");
            lbxCalculations.Items.Add(avg);
            stwrite.WriteLine(avg);
            lbxCalculations.Items.Add("Smallest Value:");
            lbxCalculations.Items.Add(nums[0]);
            stwrite.WriteLine(nums[0]);
            lbxCalculations.Items.Add("Largest value:");
            lbxCalculations.Items.Add(nums[8]);
            stwrite.WriteLine(nums[8]);
            stwrite.Close();
        }
    }
}
