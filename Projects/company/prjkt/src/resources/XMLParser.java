package resources;

import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import dao.AdminDao;
import bean.Session;

public class XMLParser {
	public static void XmlToDbConvert() {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		File folder = new File("src/xmlfiles");
		File[] listOfFiles = folder.listFiles();
		for(int j = 0; j < listOfFiles.length; j++){
			String filename = listOfFiles[j].getName();
			

		
		Map<String, String> attributeMap = new HashMap<String, String>();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();
			Document document = builder.parse("src/xmlfiles/"+filename);
			document.getDocumentElement().normalize();
			NodeList nodeLst = document.getElementsByTagName("IPDR");

			Node fstNode = nodeLst.item(0);
			NodeList second = fstNode.getChildNodes();

			for (int i = 0; i < second.getLength(); i++) {
				Node data = second.item(i);
				if (data.getNodeType() == Node.ELEMENT_NODE) {
					Element name = (Element) data;
					attributeMap.put(name.getTagName(), name.getTextContent());
				}

			}

		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Session sessionBean = new Session();
		int download = (int)Long.parseLong(attributeMap.get("serviceOctetsPassed"));
		int upload = (int)Long.parseLong(attributeMap.get("serviceOctetsReceived"));

		download = download / 1024;
		upload = upload / 1024;
		download = download / 1024;
		upload = upload / 1024;
		sessionBean.setDownload(download);
		sessionBean.setUpload(upload);
		sessionBean.setTotal(download + upload);
		sessionBean.setMac(attributeMap.get("CMmacAddress"));
		sessionBean.setIp(attributeMap.get("CMTSipAddress"));
		sessionBean.setStartDate(attributeMap.get("IPDRcreationTime"));
		sessionBean.setEndDate(attributeMap.get("IPDRendTime"));
		String dateString = sessionBean.getStartDate();
		
	    Date date = null;
		try {
			date = new SimpleDateFormat("dd-MM-yyyy").parse(dateString);
			
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}  
	    sessionBean.setSessionDate(date);
	    AdminDao adminDao = new AdminDao();
	    System.out.println(sessionBean.getMac());
	    System.out.println(sessionBean.getSessionDate());
	    adminDao.sessionUploadDao(sessionBean);
		
	    
	}
}
}
