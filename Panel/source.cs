using System;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace WinFormsApp
{
    public partial class Form1 : Form
    {
        private const int cellWidth = 50;
        private const int cellHeight = 30;

        private readonly SplitContainer splitContainer1; // 本体部
        private readonly SplitContainer splitContainer2; // ヘッダー部
        private readonly TableLayoutPanel tableLayoutPanel1; // ヘッダー
        private readonly PanelEx panel2; // グリッド線とPanel2の余計なお世話除け
        private readonly ToolTip toolTip1 = new ToolTip();
        private readonly ContextMenuStrip contextMenuStrip1 = new ContextMenuStrip();
        private readonly Size halfCellSize = new Size(cellWidth / 2, cellHeight / 2);

        private Label label;
        private Point start; // ドラッグ開始位置（panel2基準）
        private Point offset; // ドラッグ開始時のLabel内位置（label基準）

        public Form1()
        {
            InitializeComponent();

            splitContainer1 = new SplitContainer
            {
                BorderStyle = BorderStyle.Fixed3D,
                Dock = DockStyle.Fill,
            };
            splitContainer1.Panel2.AutoScroll = true;
            splitContainer1.Panel2.Paint += Panel2_Paint; // ヘッダー同期（Scrollイベントではスプリッターサイズ変更等でダメ）
            splitContainer1.SplitterMoved += SplitContainer_SplitterMoved; // スプリッター同期
            Controls.Add(splitContainer1);

            panel2 = new PanelEx(cellWidth, cellHeight)
            {
                Size = new Size(cellWidth * 24 + 1, cellHeight * 10 + 1),
            };
            panel2.MouseDown += Panel2_MouseDown;
            panel2.MouseMove += Panel2_MouseMove;
            panel2.MouseUp += Panel2_MouseUp;
            splitContainer1.Panel2.Controls.Add(panel2);

            // ヘッダー部
            splitContainer2 = new SplitContainer
            {
                BorderStyle = BorderStyle.Fixed3D,
                Dock = DockStyle.Top,
                Height = 20,
            };
            splitContainer2.SplitterMoved += SplitContainer_SplitterMoved; // スプリッター同期
            Controls.Add(splitContainer2);

            // ヘッダー
            tableLayoutPanel1 = new TableLayoutPanel
            {
                ColumnCount = 25, // 23+2 23個の数字のマスと両端に半分サイズのマスでグリッド線上に数字が来るように
                Width = cellWidth * 24 + 1,
                Height = 20,
            };

            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100f / 24 / 2));
            tableLayoutPanel1.Controls.Add(new Label());
            for (var i = 1; i < 24; i++)
            {
                tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100f / 24));
                var label = new Label
                {
                    Dock = DockStyle.Fill,
                    Text = $"{i}",
                    TextAlign = ContentAlignment.MiddleCenter,
                };
                tableLayoutPanel1.Controls.Add(label);
            }
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100f / 24 / 2));
            splitContainer2.Panel2.Controls.Add(tableLayoutPanel1);


            contextMenuStrip1.Items.Add("削除", null, ContextMenu_Click);
        }

        private void Panel2_MouseDown(object sender, MouseEventArgs e)
        {
            start = panel2.PointToClient(Cursor.Position); // 同じ new Point(e.X, e.Y);
            offset = new Point(e.X % cellWidth, e.Y % cellHeight);
            Cursor = Cursors.SizeWE;

            var x = e.X / cellWidth * cellWidth;
            var y = e.Y / cellHeight * cellHeight;

            label = new Label
            {
                BackColor = Color.MistyRose,
                BorderStyle = BorderStyle.FixedSingle,
                ContextMenuStrip = contextMenuStrip1,
                Location = new Point(x, y),
                Size = new Size(cellWidth, cellHeight),
                Text = "テスト",
                TextAlign = ContentAlignment.MiddleCenter,
            };
            label.MouseDown += Label_MouseDown;
            label.MouseMove += Label_MouseMove;
            label.MouseUp += Label_MouseUp;

            panel2.Controls.Add(label);
        }
        private void Panel2_MouseMove(object sender, MouseEventArgs e)
        {
            if (label != null) TryResize(label);
        }
        private void Panel2_MouseUp(object sender, MouseEventArgs e)
        {
            Cursor = Cursors.Default;
            if (label != null) toolTip1.Hide(label);
            label = null;
        }

        private void Label_MouseDown(object sender, MouseEventArgs e)
        {
            if (sender is Label label)
            {
                // リサイズ時に反対の辺をstartに設定
                offset = new Point(e.X, e.Y);
                if (e.X < 8)
                {
                    start = label.Location + label.Size - halfCellSize;
                }
                if (label.Width - 8 < e.X)
                {
                    start = label.Location + halfCellSize;
                }
            }
        }
        private void Label_MouseMove(object sender, MouseEventArgs e)
        {
            if (sender is Label label)
            {
                if (e.Button == MouseButtons.None)
                {
                    if (e.X < 8 || label.Width - 8 < e.X) label.Cursor = Cursors.SizeWE;
                    else label.Cursor = Cursors.Hand;
                }

                if (e.Button == MouseButtons.Left)
                {
                    if (label.Cursor == Cursors.SizeWE) TryResize(label);
                    if (label.Cursor == Cursors.Hand) TryMove(label);
                }
            }
        }
        private void Label_MouseUp(object sender, MouseEventArgs e)
        {
            toolTip1.Hide((Label)sender);
        }

        private void ContextMenu_Click(object sender, EventArgs e)
        {
            if (sender is ToolStripMenuItem item && item.Owner is ContextMenuStrip contextMenu)
            {
                if (contextMenu.SourceControl is Label label)
                {
                    label.MouseDown -= Label_MouseDown;
                    label.MouseMove -= Label_MouseMove;
                    label.MouseUp -= Label_MouseUp;
                    panel2.Controls.Remove(label);
                }
            }
        }

        // スプリッターの同期
        private void SplitContainer_SplitterMoved(object sender, SplitterEventArgs e)
        {
            if (sender == splitContainer1 && splitContainer2 != null)
                splitContainer2.SplitterDistance = splitContainer1.SplitterDistance;
            if (sender == splitContainer2 && splitContainer1 != null)
                splitContainer1.SplitterDistance = splitContainer2.SplitterDistance;
        }
        // ヘッダーの同期
        private void Panel2_Paint(object sender, PaintEventArgs e)
        {
            var p = splitContainer1.Panel2.AutoScrollPosition;
            tableLayoutPanel1.Left = p.X;
        }

        private void TryMove(Label target)
        {
            var p = panel2.PointToClient(Cursor.Position);
            var x = (p.X - offset.X + cellWidth / 2) / cellWidth * cellWidth;
            var y = (p.Y - offset.Y + cellHeight / 2) / cellHeight * cellHeight;

            var rect = target.Bounds;
            rect.X = x;
            rect.Y = y;
            TrySetBounds(target, rect);
        }
        private void TryResize(Label target)
        {
            var end = panel2.PointToClient(Cursor.Position);
            var s = start.X / cellWidth * cellWidth;
            var e = end.X / cellWidth * cellWidth;
            var rect = target.Bounds;

            if (start.X < end.X)
            {
                rect.X = s; // 本来不要なはずだが謎挙動に悩まされた...
                rect.Width = e - s + cellWidth;
            }
            else
            {
                rect.X = e;
                rect.Width = s - e + cellWidth;
            }
            TrySetBounds(target, rect);
        }
        private void TrySetBounds(Label target, Rectangle rect)
        {
            if (target.Bounds == rect) return; // ToolTipがちらつくし無駄なので

            // panel2の中で自分以外と交差するものがあったら動かさない（＝重ねられない）
            foreach (var label in panel2.Controls.OfType<Label>())
            {
                if (label == target) continue;
                if (label.Bounds.IntersectsWith(rect)) return;
            }
            target.Bounds = rect;

            var t = $"Location: {target.Location}\nSize: {target.Size}";
            toolTip1.Show(t, target, 0, -50);
        }
    }

    public class PanelEx : Panel // グリッド線付きPanel
    {
        private readonly int cellWidth;
        private readonly int cellHeight;

        public PanelEx(int cellWidth, int cellHeight)
        {
            this.cellWidth = cellWidth;
            this.cellHeight = cellHeight;
            DoubleBuffered = true;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var right = ClientRectangle.Right;
            var bottom = ClientRectangle.Bottom;

            for (var x = 0; x < right; x += cellWidth)
            {
                e.Graphics.DrawLine(Pens.Gray, x, 0, x, bottom);
            }
            for (var y = 0; y < bottom; y += cellHeight)
            {
                e.Graphics.DrawLine(Pens.Gray, 0, y, right, y);
            }
        }
    }
}
