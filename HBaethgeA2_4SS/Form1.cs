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
    public partial class frmSplash : Form
    {
        public int timeLeft
        {
            get;
            set;
        }
        public frmSplash()
        {
            InitializeComponent();
        }
        private void frmSplash_Load(object sender, EventArgs e)
        {
            timeLeft = 15;
            tmrSplash.Start();
        }
        private void tmrSplash_Tick(object sender, EventArgs e)
        {
            if(timeLeft > 0)
            {
                timeLeft -= 1;
            }
            else
            {
                tmrSplash.Stop();
                new frmMain().Show();
                this.Hide();
            }
        }        
    }
}
