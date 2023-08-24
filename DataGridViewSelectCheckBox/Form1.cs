using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // DataGridViewの設定
            dataGridView1.MultiSelect = true;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            // 列を追加
            DataGridViewCheckBoxColumn checkBoxColumn = new DataGridViewCheckBoxColumn();
            dataGridView1.Columns.Add(checkBoxColumn);
            dataGridView1.Columns.Add("Column2", "Column2");
            dataGridView1.Columns.Add("Column3", "Column3");

            // チェックボックス列以外のセルをReadOnlyに設定
            foreach (DataGridViewColumn column in dataGridView1.Columns)
            {
                if (column.Index != 0) // チェックボックス列以外の列
                {
                    column.ReadOnly = true;
                }
            }

            // イベントハンドラの設定
            dataGridView1.CellClick += DataGridView1_CellClick;
            dataGridView1.KeyDown += DataGridView1_KeyDown;
        }

        private void DataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            // チェックボックス列以外のセルがクリックされた場合、選択行を変更
            if (e.RowIndex >= 0 && e.ColumnIndex > 0)
            {
                dataGridView1.Rows[e.RowIndex].Selected = true;
            }
        }

        private void DataGridView1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space)
            {
                // 選択中の行のチェックボックスにチェックを入れる
                foreach (DataGridViewRow row in dataGridView1.SelectedRows)
                {
                    DataGridViewCheckBoxCell checkBoxCell = row.Cells[0] as DataGridViewCheckBoxCell;
                    if ((checkBoxCell.Value == null) ||
                        (checkBoxCell.Value.Equals(false)))
                    {
                        checkBoxCell.Value = true;
                    }
                    else
                    {
                        checkBoxCell.Value = false;
                    }
                }
                e.Handled = true;
            }
        }
    }
}
