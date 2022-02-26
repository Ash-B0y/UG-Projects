package bean;
public class Package {

	private String packages;
	private int dataInGB;
	private int monthlyCharges;
	private float chargesAfterLimit;
	public String getPackages() {
		return packages;
	}
	public void setPackages(String packages) {
		this.packages = packages;
	}
	public int getDataInGB() {
		return dataInGB;
	}
	public void setDataInGB(int dataInGB) {
		this.dataInGB = dataInGB;
	}
	public int getMonthlyCharges() {
		return monthlyCharges;
	}
	public void setMonthlyCharges(int monthlyCharges) {
		this.monthlyCharges = monthlyCharges;
	}
	public float getChargesAfterLimit() {
		return chargesAfterLimit;
	}
	public void setChargesAfterLimit(float chargesAfterLimit) {
		this.chargesAfterLimit = chargesAfterLimit;
	}
	
}
