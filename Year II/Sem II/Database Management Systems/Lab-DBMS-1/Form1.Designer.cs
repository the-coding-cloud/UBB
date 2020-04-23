namespace Lab_DBMS_1
{
    partial class Form1
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
            this.dataGridViewAirports = new System.Windows.Forms.DataGridView();
            this.dataGridViewCountries = new System.Windows.Forms.DataGridView();
            this.airportsLabel = new System.Windows.Forms.Label();
            this.countriesLabel = new System.Windows.Forms.Label();
            this.updateButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAirports)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCountries)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewAirports
            // 
            this.dataGridViewAirports.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewAirports.Location = new System.Drawing.Point(291, 34);
            this.dataGridViewAirports.Name = "dataGridViewAirports";
            this.dataGridViewAirports.Size = new System.Drawing.Size(511, 365);
            this.dataGridViewAirports.TabIndex = 0;
            // 
            // dataGridViewCountries
            // 
            this.dataGridViewCountries.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewCountries.Location = new System.Drawing.Point(16, 34);
            this.dataGridViewCountries.Name = "dataGridViewCountries";
            this.dataGridViewCountries.Size = new System.Drawing.Size(220, 365);
            this.dataGridViewCountries.TabIndex = 1;
            // 
            // airportsLabel
            // 
            this.airportsLabel.AutoSize = true;
            this.airportsLabel.Font = new System.Drawing.Font("Helvetica", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.airportsLabel.Location = new System.Drawing.Point(287, 9);
            this.airportsLabel.Name = "airportsLabel";
            this.airportsLabel.Size = new System.Drawing.Size(76, 22);
            this.airportsLabel.TabIndex = 2;
            this.airportsLabel.Text = "Airports";
            // 
            // countriesLabel
            // 
            this.countriesLabel.AutoSize = true;
            this.countriesLabel.Font = new System.Drawing.Font("Helvetica", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.countriesLabel.Location = new System.Drawing.Point(12, 9);
            this.countriesLabel.Name = "countriesLabel";
            this.countriesLabel.Size = new System.Drawing.Size(93, 22);
            this.countriesLabel.TabIndex = 3;
            this.countriesLabel.Text = "Countries";
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(291, 421);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(75, 23);
            this.updateButton.TabIndex = 8;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(863, 466);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.countriesLabel);
            this.Controls.Add(this.airportsLabel);
            this.Controls.Add(this.dataGridViewCountries);
            this.Controls.Add(this.dataGridViewAirports);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAirports)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCountries)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewAirports;
        private System.Windows.Forms.DataGridView dataGridViewCountries;
        private System.Windows.Forms.Label airportsLabel;
        private System.Windows.Forms.Label countriesLabel;
        private System.Windows.Forms.Button updateButton;
    }
}

