import java.util.ArrayList;

import org.apache.commons.math3.distribution.MultivariateNormalDistribution;
import org.apache.commons.math3.linear.ArrayRealVector;
import org.apache.commons.math3.linear.BlockRealMatrix;
import org.apache.commons.math3.linear.CholeskyDecomposition;
import org.apache.commons.math3.linear.LUDecomposition;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;

public class Entity implements Comparable<Entity> {
	private double x, y;
	private double sigma1, sigma2;
	private double alfa;
	AlmostLambda function;
	
	public Entity(AlmostLambda func){
		function = func;
		BlockRealMatrix rndHelp = new BlockRealMatrix(1,1);
		rndHelp.setEntry(0, 0, 20);
		double[] mean = new double[1];
		mean[0] = 0.0;
		MultivariateNormalDistribution rnd = new MultivariateNormalDistribution(mean, rndHelp.getData());
		x = rnd.sample()[0];
		y = rnd.sample()[0];
		rndHelp.setEntry(0, 0, 10);
		rnd = new MultivariateNormalDistribution(mean, rndHelp.getData());
		sigma1 = rnd.sample()[0];
		sigma2 = rnd.sample()[0];
		rndHelp.setEntry(0, 0, 1);
		rnd = new MultivariateNormalDistribution(mean, rndHelp.getData());
		alfa = rnd.sample()[0];
	}
	
	public Entity(double value1, double value2, double deviation1, double deviation2, double rad, AlmostLambda func){
		x = value1;
		y = value2;
		sigma1 = deviation1;
		sigma2 = deviation2;
		y = rad;
		function = func;
	}
	
	public double getValue(){
		return function.evaluate(x,y);
	}
	
	public ArrayList<Entity> crossOver(Entity e){
		double randAlfa = 2 * Math.random() - 0.5;
		Entity e1 = new Entity(x, y, randAlfa * sigma1 + (1 - randAlfa) * e.sigma1,
				randAlfa * sigma2 + (1 - randAlfa) * e.sigma2, randAlfa * alfa + (1 - randAlfa) * e.alfa, function);
		Entity e2 = new Entity(e.x, e.y, randAlfa * e.sigma1 + (1 - randAlfa) * sigma1,
				randAlfa * e.sigma2 + (1 - randAlfa) * sigma2, randAlfa * e.alfa + (1-randAlfa) * alfa, function);
		ArrayList<Entity> retVal = new ArrayList<Entity>();
		retVal.add(e1);
		retVal.add(e2);
		return retVal;
	}
	
	public void mutate(){
		BlockRealMatrix rndHelp = new BlockRealMatrix(1,1);
		rndHelp.setEntry(0, 0, 1);
		double[] mean = new double[1];
		mean[0] = 0.0;
		MultivariateNormalDistribution rnd = new MultivariateNormalDistribution(mean, rndHelp.getData());
		
		double tau = 1.0 / Math.sqrt(4);
		double tau2 = 1.0 / Math.sqrt(2*Math.sqrt(2));
		sigma1 = Math.max(Math.pow(10, -11), sigma1*Math.pow(2.718281828, tau*rnd.sample()[0] + tau2*rnd.sample()[0]));
		sigma2 = Math.max(Math.pow(10, -11), sigma2*Math.pow(2.718281828, tau*rnd.sample()[0] + tau2*rnd.sample()[0]));
		
		double rad = 0.0872665;
		alfa = alfa + rad * rnd.sample()[0];
		
		BlockRealMatrix C = new BlockRealMatrix(2,2);
		C.setEntry(0, 0, sigma1*sigma1);
		C.setEntry(1, 1, sigma2*sigma2);
		C.setEntry(0, 1, 0.5 * (sigma1 * sigma1 - sigma2 * sigma2) * Math.tan(2 * alfa));
		C.setEntry(1, 0, C.getEntry(0, 1));
		
		CholeskyDecomposition cholesky = new CholeskyDecomposition(C);
		
		ArrayRealVector vector = new ArrayRealVector(2);
		vector.setEntry(0, rnd.sample()[0]);
		vector.setEntry(1, rnd.sample()[0]);
		
		RealVector newX = cholesky.getL().operate(vector);
		x = newX.getEntry(0);
		y = newX.getEntry(1);
	}

	@Override
	public int compareTo(Entity arg0) {
		if(getValue() < arg0.getValue())
			return -1;
		if(getValue() > arg0.getValue())
			return 1;
		return 0;
	}
}
