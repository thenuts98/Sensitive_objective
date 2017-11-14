import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.border.*;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.Font;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import java.io.File;


public class Musaic extends JFrame implements ActionListener {
	
	Clip clip;
	
	String path = Musaic.class.getResource("").getPath();
	
	Font f1 = new Font("a뉴굴림4", Font.PLAIN, 30);
	
	JPanel panel = new JPanel();
	
	JPanel colorP[] = new JPanel[8];
	JPanel soundP[] = new JPanel[8];
	
	JLabel colorL[] = new JLabel[8];
	
	String colors[] = {"빨강", "분홍", "주황", "노랑", "초록", "파랑", "군청", "보라"};
	
	String sounds[] = {"낮은 도", "레", "미", "파", "솔", "라", "시", "높은 도", "드럼", "심벌즈", "박수"};
	
	JComboBox selector[] = new JComboBox[8];
	
	JButton applyButton = new JButton("적용");
	JButton playButton = new JButton("시작");
	
	File file[] = new File[8];
	
	
	
	public Musaic(String title) {
		setTitle(title);		
	}
	
	public void CreateFrame()
	{
		panel.setLayout(new GridLayout(9, 2));
		
		for(int i=0; i<selector.length; i++)
		{
			selector[i] = new JComboBox(sounds);
			selector[i].setSelectedItem(sounds[i]);
			
			selector[i].setSize(120, 60);			
		}
		
		
		
		for(int i=0; i<colorL.length; i++)
		{			
			colorL[i] = new JLabel(colors[i]);
			colorL[i].setFont(f1);
			colorL[i].setForeground(Color.WHITE);
			
			colorP[i] = new JPanel();			
			soundP[i] = new JPanel();					
		}
		
		colorP[0].setBackground(new Color(255,0,0));
		colorP[1].setBackground(new Color(255,0,255));
		colorP[2].setBackground(new Color(255,165,0));
		colorP[3].setBackground(new Color(255,255,0));
		colorP[4].setBackground(new Color(0,255,0));
		colorP[5].setBackground(new Color(0,0,255));
		colorP[6].setBackground(new Color(0,0,128));
		colorP[7].setBackground(new Color(128,0,128));
		
		for(int i=0; i<colorL.length; i++)
		{
			colorP[i].add(colorL[i]);
			soundP[i].add(selector[i]);	
			
			panel.add(colorP[i], new GridLayout(i,1));
			panel.add(soundP[i], new GridLayout(i,2));
		}
		applyButton.setFont(f1);
		playButton.setFont(f1);
		
		applyButton.setForeground(Color.BLACK);
		playButton.setForeground(Color.BLACK);
		panel.add(applyButton, new GridLayout(9,1));
		panel.add(playButton, new GridLayout(9,2));
		
		
		file[0] = new File(path+"DO1.wav");
		file[1] = new File(path+"RE.wav");
		file[2] = new File(path+"MI.wav");
		file[3] = new File(path+"FA.wav");
		file[4] = new File(path+"SOL.wav");
		file[5] = new File(path+"RA.wav");
		file[6] = new File(path+"SI.wav");
		file[7] = new File(path+"DO2.wav");
		
		
		SoundPlay(file[0]);
		SoundPlay(file[2]);
		SoundPlay(file[4]);
		
		this.add(panel);
		
		setBounds(300, 300, 300, 500);
		setVisible(true);
	}
	
	void SoundPlay(File x)
	{
		AudioInputStream stream;
		AudioFormat format;
		DataLine.Info info;
		
		try {
			stream = AudioSystem.getAudioInputStream(x);
			format = stream.getFormat();
			info = new DataLine.Info(Clip.class, format);
			clip = (Clip)AudioSystem.getLine(info);
			clip.open(stream);
			clip.start();
		} catch (Exception e) {
			
		}
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Musaic frame = new Musaic("Musaic");
		frame.CreateFrame();

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}

}
