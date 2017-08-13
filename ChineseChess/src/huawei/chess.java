package huawei;

import java.util.LinkedList;

class  coordinate
{
	private int currentRow;
	private int currentCol;
	coordinate(int currentRow,int currentCol)
	{
		this.currentCol=currentCol;
		this.currentRow=currentRow;
	}
	public int getX() {
		return currentRow;
	}
	public int getY() {
		return currentCol;
	}
}

public class chess
{
	static LinkedList<chessPiece> chessOnBoard= new LinkedList<chessPiece>();
	private static chessPoint[][] chessBoard;
	public int add_piece(chessType pieceType,chessOwner pieceOwner,int currentRow, int currentCol) {
		chessOnBoard.add(new chessPiece(pieceType,pieceOwner,currentRow, currentCol));
		
		return 0;
		
	}
	public static void main(String[] args)
	{
		chessPointInit();
		chessPiece newPiece_1 = new chessPiece(chessType.Ju,chessOwner.Hong,0,1);
		System.out.println(newPiece_1);
//		for (chessType i:chessType.values())
//			System.out.println(i);
	}
	public static int chessPointInit() {
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<9;j++)
			{
				chessBoard[i][j]=new chessPoint(i,j);		
			}		
		}
		return 0;
	}
	public boolean checkJudge()
	{
		
		return true;
	}
}
enum chessType
{
	Ju(1),Ma(2),Pao(3),Xiang(4),Shi(5),Bing(6),Zu(7),Shuai(8),Jiang(9);
	private int No;
	private chessType(int No)
	{
		this.No=No;
	}
}
enum chessOwner
{
	Hong(1),Hei(2);
	private int owernership;
	private chessOwner(int owernership)
	{
		this.owernership=owernership;
	}
}
class chessPiece
{
	private chessType pieceType;
	private chessOwner pieceOwner;
	private coordinate xy;
	public int nextMove() {
		switch (pieceType) {
		case Ju:
			
			break;

		default:
			break;
		}
		
		return 0;
	}
	chessPiece(chessType pieceType,chessOwner pieceOwner,int currentRow, int currentCol)
	{
		this.pieceType=pieceType;
		this.pieceOwner=pieceOwner;
		this.xy = new coordinate(currentRow, currentCol);
		
	}
	public String toString()
	{		
		return("This is a "+pieceOwner+' '+pieceType+", it's on row "+this.xy.getX()+", col "+this.xy.getY()+".");
	}

}
class chessPoint
{
	private coordinate xy;	
	private chessType chess_on_point;
	private chessOwner chess_owner;
	boolean isEmpty = true;
	public chessPoint(int currentRow,int currentCol) {
		// TODO Auto-generated constructor stub
		xy = new coordinate(currentRow,currentCol);
	}
	public int putChessOnBoard(chessType chess_on_point,chessOwner chess_owner)
	{
		this.chess_on_point = chess_on_point;
		this.chess_owner = chess_owner;
		isEmpty=false;
		return 0;
	}
	public int removeChessOnBoard()
	{
		this.chess_on_point = null;
		this.chess_owner = null;
		isEmpty=true;
		return 0;
	}
	public boolean isEmpty(coordinate xy)
	{
		return isEmpty;
	}
}