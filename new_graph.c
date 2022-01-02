#include<stdlib.h>
#include<stdio.h>
#include"GRAPH_.h"
int graph_size;

void deleteGraph_cmd(pnode* head)
{
    if (!*head)
    {
        return;
    }
    pnode temp = *head;
    while (temp)
    {
        pnode free_node = temp;
        pedge temp_edge = temp->edges;
        while (temp_edge)
        {
            pedge free_edge = temp_edge;
            temp_edge=temp_edge->next;
            free(free_edge);
        }
        temp=temp->next;
        free(free_node);
        
    }
    
}
pnode get_node(pnode *head, int id)
{
    if(!*head)
    {
        return NULL;
    }
    if((*head)->node_num == id)
    {
        return *head;
    }
    pnode temp = *head;
    while (temp->next!= NULL)
    {
        if (temp->node_num == id)
        {
            pnode ans = temp;
            return ans;
        }
        temp = temp->next;
    }
    if(temp->node_num==id)
    {
        pnode ans = temp;
        return ans;
    }
    return NULL;
}
void add_node(pnode *head,pnode n)
{
    if(!*head)
    {
        *head = n;
        return;
    }
    pnode copy = *head;
    while(copy->next)
    {
        copy = copy->next;
    }
    copy->next = n;
}
void add_edge(pnode src, pnode dest, int w)
{
    pedge h = src->edges;
    pedge e = (pedge)malloc(sizeof(edge));
    if (e==NULL)
    {
        printf("error");
        return;
    }
    e->endpoint = dest;
    e->weight = w;
    e->next = NULL;
    if(!h)
    {
        h = e;
        src->edges=h;
        return;
    }
    pedge copy = h;
    while(copy->next)
    {
        copy = copy->next;
    }
    copy->next = e;
}
char build_graph_cmd(pnode *head)
{
    if (head != NULL)
    {
        deleteGraph_cmd(head);
    }
    int id,dest_id,edge_val,num_of_node,i;
    scanf(" %d",&num_of_node);
    graph_size = num_of_node;
    for (i=0;i<num_of_node;i++)
    {
        pnode v = (pnode)malloc(sizeof(node));
        if (v==NULL)
        {
            printf("error");
            return ' ';
        }
        v->node_num = i;
        pedge H = (pedge)malloc(sizeof(edge));
        H = NULL;
        v->edges = H;
        add_node(head,v);
    }
    //printGraph_cmd(*head);
    //printf("if you want add edges for node, enter n\n");
    char c;
    scanf(" %c",&c);
    while(c!='A'&&c!='B'&&c!='D'&&c!='S'&&c!='T'&&c!=EOF)
    {
        //printf("enter node id\n");
        scanf(" %c",&c);
               
        pnode src = get_node(head,c-'0');
        //printf("enter dest\n");
        scanf(" %c",&c);
        while(c!='n'&&c!='A'&&c!='B'&&c!='D'&&c!='S'&&c!='T')
        {
            pnode dest = get_node(head,c-'0');
            //printf("enter edge w\n");
            scanf(" %c",&c);
            add_edge(src,dest,c-'0');
            //printf("for more edge, pleas enter dest, for more node enter n\n");
            scanf(" %c",&c);
        }
    }
    return c;
}
void printGraph_cmd(pnode head)
{
    pnode nodes = head;
    printf("graph:\n");
    while (nodes)
    {
        printf("node id- %d ",nodes->node_num);
        pedge ed = nodes->edges;
        while (ed)
        {
            printf("  dest- %d, w -%d  ",ed->endpoint->node_num,ed->weight);
            ed=ed->next;
        }
        printf("\n");
        nodes = nodes->next;
    }
    
}
char insert_node_cmd(pnode *head)
{
    char c;
    int id;
    scanf(" %d",&id);
    pnode new_node = (pnode)malloc(sizeof(node));
    new_node->node_num = id;
    if (get_node(head,id)!=NULL)
    {
        pnode copy = *head;
        pnode temp = get_node(head,id);
        if (temp->node_num == (*head)->node_num)
        {
            new_node->next = (*head)->next;
            //free(temp);
            *head = new_node;
        }
        else
        {
            pnode copy = *head;
            pnode prev = *head;
            while(prev->next && prev->next->node_num != id)
            {
                prev = prev-> next;
                copy = copy -> next;
            }
            if(!prev->next->next)
            {
                prev->next = new_node;
                //pnode t= copy->next;
                //free(t);
            }
            else
            {
                //pnode *old = &(prev->next);
                pnode *t = &(prev->next->next);
                prev->next = new_node;
                new_node->next = *t;
                //free(*old);
                //free(temp);
            }

        }
    }
    else
    {
        add_node(head,new_node);
        graph_size += 1;
    }
    //printf("if you want add edges for node, enter dest\n");
    scanf(" %c",&c);
    while (c!='A'&&c!='B'&&c!='D'&&c!='S'&&c!='T'&&c!=EOF)
    {
        pnode dest = get_node(head,c-'0');
        //printf("enter edge w\n");
        scanf(" %c",&c);
        add_edge(new_node,dest,c-'0');
        //printf("for more edge, pleas enter dest\n");
        scanf(" %c",&c);
    }
    return c;
}
void remove_edge(pedge *head,pedge to_remove)
{
    if ((*head)->endpoint->node_num==to_remove->endpoint->node_num)
    {
        *head = (*head)->next;
        free(to_remove);
        return;
    }
    pedge copy = *head;
    pedge prev = *head;
    while(prev->next&&prev->next->endpoint!=to_remove->endpoint)
    {
        prev = prev-> next;
        copy = copy -> next;
    }
    if(!prev->next->next){
        prev->next = NULL;
        copy = copy->next;
        free(copy);
        return;
    }
    prev->next = prev->next->next;
    copy = copy->next;
    free(copy);
}
void delete_node_cmd(pnode *head)
{
    graph_size -= 1;
    pnode copy = *head;
    int id;
    scanf("%d",&id);
    pnode temp = get_node(head,id);
    while (copy)
    {
        pedge edge_copy = copy->edges;
        while (edge_copy)
        {
            if (edge_copy->endpoint->node_num==id)
            {
                remove_edge(&(copy->edges),edge_copy);
            }
            edge_copy = edge_copy->next;
        }
        copy = copy->next;
    }
    if (id == (*head)->node_num)
    {
        *head = (*head)->next;
        free(temp);
        return;
    }
    copy = *head;
    pnode prev = *head;
    while(prev->next && prev->next->node_num != id)
    {
        prev = prev-> next;
        copy = copy -> next;
    }
    if(!prev->next->next)
    {
        prev->next = NULL;
        copy = copy->next;
        free(copy);
        return;
    }
    copy = copy->next;
    pnode t = copy;
    prev->next = prev->next->next;
    free(t);
}
int findid(int index,int* arr)
{
    for (int i = 0; i < graph_size; i++)
    {
        if(index==arr[i])
        {
            return i;
        }
    }
    return -1;
}
void shortsPath_cmd(pnode head)
{
    int src,dest,i,j,g;
    int max = 2000000;
    int *find_id = (int *)malloc(graph_size*sizeof(int));
    pnode temp = head;
    for ( i = 0; i < graph_size; i++,temp =temp->next)
    {
        find_id[i] = temp->node_num;
    }
    
    int** mat =(int **)malloc(graph_size*sizeof(int *));
    for ( i = 0; i < graph_size; i++)
    {
        mat[i] = (int *)malloc(graph_size*sizeof(int));
    }
    for ( i = 0; i < graph_size; i++)
    {
        for (j = 0; j < graph_size; j++)
        {
            if(i==j)
            {
                mat[i][j] = 0;
            }
            else
                mat[i][j] = max;
        }
        
    }
    pnode copy = head;
    while(copy)
    {
        pedge ed = copy->edges;
        while (ed)
        {
            mat[findid(copy->node_num,find_id)][findid(ed->endpoint->node_num,find_id)]=ed->weight;
            ed=ed->next;
        }
        copy=copy->next;
    }
    for ( i = 0; i < graph_size; i++)
    {
        for ( j = 0; j < graph_size; j++)
        {
            for ( g = 0; g < graph_size; g++)
            {
                if (mat[g][j] > mat[g][i]+mat[i][j])
                    mat[g][j] = mat[g][i]+mat[i][j];
            }
            
        }
        
    }
    scanf("%d %d",&src,&dest);
    if(mat[findid(src,find_id)][findid(dest,find_id)]==max)
    {
        printf("Dijsktra shortest path: %d\n",-1);
    }
    else
        printf("Dijsktra shortest path: %d\n",mat[findid(src,find_id)][findid(dest,find_id)]);
}
int get_id(int c, int **dist,int id)
{
    int i, ans=-1;
    for ( i = 0; i < c-1; i++)
    {
        if(dist[0][i+1]==id)
        {
            ans = i+1;
        }
    }
    return ans;
    
}
int path(int c, int **dist, int start, int *p)
{
    int count = 0,i;
    for ( i = 0; i < start-1; i++)
    {
        int src = get_id(c,dist,p[i]);
        int dest = get_id(c,dist,p[i+1]);
        int d = dist[src][dest];
        if(d==-1)
        {
            return 2000000;
        }
        count+=d;
    }
    return count;
    
}
int rec_tsp(int c,int *cities, int *p, int **dist, int start, int over)
{
    if (over == 0)
    {
        return path(c,dist,start,p);
    }
    int min = 2000000,i,j;
    for(i=0;i<over;i++)
    {
        p[start] = cities[i];
        //int *temp = (int *)malloc((over-1)*sizeof(int));
        int temp[over-1];
        int f=0;
        for (j = 0; j < over; j++)
        {
           if(j!=i)
           {
               temp[f]=cities[j];
               f++;
           }
        }
        int current = rec_tsp(c,temp,p,dist,start+1,over-1);
        if(current!=-1&&min>current)
        {
            min = current;
        }
        
    }
    return min;
}
void TSP_cmd(pnode head)
{
    int c,cost;
    int src,dest,i,j,g;
    int max = 2000000;
    int *find_id = (int *)malloc(graph_size*sizeof(int));
    pnode temp = head;
    for ( i = 0; i < graph_size; i++,temp =temp->next)
    {
        find_id[i] = temp->node_num;
    }
    int** mat =(int **)malloc(graph_size*sizeof(int *));
    for ( i = 0; i < graph_size; i++)
    {
        mat[i] = (int *)malloc(graph_size*sizeof(int));
    }
    for ( i = 0; i < graph_size; i++)
    {
        for (j = 0; j < graph_size; j++)
        {
            if(i==j)
            {
                mat[i][j] = 0;
            }
            else
                mat[i][j] = max;
        }
        
    }
    pnode copy = head;
    while(copy)
    {
        pedge ed = copy->edges;
        while (ed)
        {
            mat[findid(copy->node_num,find_id)][findid(ed->endpoint->node_num,find_id)]=ed->weight;
            ed=ed->next;
        }
        copy=copy->next;
    }
    for ( i = 0; i < graph_size; i++)
    {
        for ( j = 0; j < graph_size; j++)
        {
            for ( g = 0; g < graph_size; g++)
            {
                if (mat[g][j] > mat[g][i]+mat[i][j])
                    mat[g][j] = mat[g][i]+mat[i][j];
            }
            
        }
        
    }
    scanf(" %d",&c);
    int *cities = (int *)malloc(c*sizeof(int));
    for (i=0;i < c;i++)
    {
        scanf(" %d",&cities[i]);
    }
    int** dist =(int **)malloc((c+1)*sizeof(int *));
    for ( i = 0; i < c+1; i++)
    {
        dist[i] = (int *)malloc((c+1)*sizeof(int));
    }
    for ( i = 0; i < c; i++)
    {
        dist[0][i+1] = cities[i];
        dist[i+1][0] = cities[i];
    }
    for ( i = 0; i < c; i++)
    {
        for (j=0; j<c; j++)
        {
            dist[i+1][j+1]=mat[findid(cities[i],find_id)][findid(cities[j],find_id)];
        }
    }
    
    int *p = (int *)malloc(c*sizeof(int));
    int ans = rec_tsp(c+1,cities,p,dist,0,c);
    if (ans == max)
    {
        printf("TSP shortest path: %d\n",-1) ;
    }
    else
        printf("TSP shortest path: %d \n",ans);
    
    
    
}

int main()
{
    pnode head = NULL;
    char c,d;
    scanf(" %c",&c);
    while (c != EOF && c != '~')
    {
        d=' ';
        if(c=='A')
        {
            //printf("start new graph\n");
            d = build_graph_cmd(&head);
        }
        if(c=='B')
        {
            //printf("add node\n");
            d = insert_node_cmd(&head);
        }
        if(c=='D')
        {
            //printf("delete node\n");
            delete_node_cmd(&head);
        }
        if(c=='S')
        {
            //printf("short path\n");
            shortsPath_cmd(head);
        }
        if(c=='T')
        {
            //printGraph_cmd(head);
            //printf("travel problem\n");
            TSP_cmd(head);
        }
        if (d==' ')
        {
            scanf(" %c",&c);
        }
        else
        {
            c = d;
        }
        if(d==EOF)
        {
            printf("error");
            break;
        }
        if (c==EOF)
        {
            printf("error");
            break;
        }
        
    }
    deleteGraph_cmd(&head);
}