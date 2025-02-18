package DateBase;

import java.util.ArrayList;
import java.util.List;

public class Information implements ClientHelper{
    public List<Client> clients = new ArrayList<>();

    public Information(List<Client> list){
        clients = list;
        ClearSameClients();
        for (int i = 0; i<clients.size(); i++){
            clients.get(i).id = i;
            for (int j = 0; j<clients.get(i).credits.size(); j++){
                clients.get(i).credits.get(j).id = i;
            }
        }
    }

    public Client SearchID(int id){
        Client cl = new Client();
        for (int i = 0; i<clients.size(); i++)
            if (clients.get(i).id == id) cl =  clients.get(i);
        return cl;
    }

    @Override
    public List<Client> GetDepters(){
        List<Client> depters = new ArrayList<>();
        for (int i = 0; i<clients.size(); i++)
            if (clients.get(i).deptSum > 0) depters.add(clients.get(i));
        return depters;
    }

    @Override
    public List<Credit> GetUnpaidCredits()
    {
        List<Credit> credits = new ArrayList<Credit>();
        for (int i = 0; i<clients.size(); i++){
            credits.addAll(clients.get(i).nonpayedCredits);
        }
        return credits;
    }

    @Override
    public float GetCreditSum(){
        float sum = 0;
        for (int i = 0; i<clients.size(); i++)
            sum += clients.get(i).deptSum;
        return sum;
    }

    public void ClearSameClients(){
        for (int i = 0; i<clients.size(); i++){
            boolean flag = false;
            int index = i;
            for (int j = i+1; j<clients.size(); j++){
                if (clients.get(i).newPass == clients.get(j).newPass || clients.get(i).newPass == clients.get(j).oldPass || clients.get(i).oldPass == clients.get(j).newPass) {
                    flag = true;
                    index = j;
                }

            }
            if (flag)
            {
                clients.get(index).credits.addAll(clients.get(i).credits);
                clients.remove(i);
            }
        }
    }
}
