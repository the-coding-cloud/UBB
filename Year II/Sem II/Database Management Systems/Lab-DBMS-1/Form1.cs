using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_DBMS_1
{
    public partial class Form1 : Form
    {
        private SqlConnection connection;
        private SqlDataAdapter daAirport, daCountry;
        private DataSet ds;
        private SqlCommandBuilder commandBuilder;
        private BindingSource bsAirport, bsCountry;
        public Form1()
        {
            InitializeComponent();
            LoadData();
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            daAirport.Update(ds, "Airport");
            LoadData();
        }

        private void LoadData()
        {
            connection = new SqlConnection(GetConnectionString());

            ds = new DataSet();

            daAirport = new SqlDataAdapter("select * from Airport", connection);
            daCountry = new SqlDataAdapter("select * from Country", connection);

            commandBuilder = new SqlCommandBuilder(daAirport);

            daAirport.Fill(ds, "Airport");
            daCountry.Fill(ds, "Country");

            DataRelation dr = new DataRelation("FK__Airport__Country__3A81B327", ds.Tables["Country"].Columns["CountryID"], ds.Tables["Airport"].Columns["CountryID"]);
            ds.Relations.Add(dr);

            bsAirport = new BindingSource();
            bsCountry = new BindingSource();

            bsCountry.DataSource = ds;
            bsCountry.DataMember = "Country";

            bsAirport.DataSource = bsCountry;
            bsAirport.DataMember = "FK__Airport__Country__3A81B327";

            dataGridViewAirports.DataSource = bsAirport;
            dataGridViewCountries.DataSource = bsCountry;
        }
        private static String GetConnectionString()
        {
            return "Data Source=OANA\\SQLEXPRESS;" +
                   "Initial Catalog=Airline;" +
                   "Integrated Security = true;";
        }
    }
}
