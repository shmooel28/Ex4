#include<stdlib.h>
#include<stdio.h>
#include"GRAPH_.h"
int graph_size;
void free_edge(pedge *head)
{
    pedge *temp = head;
    while (*temp)
    {
        pedge free_edge = *temp;
        *temp=(*temp)->next;
        free(free_edge);
    }
}
void deleteGraph_cmd(pnode* head)
{
    
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
        free(temp_edge);
        temp=temp->next;
        free(free_node);
        
    }
    graph_size = 0;
    *head = NULL;
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
        (*head)->next = NULL;
        return;
    }
    pnode copy = *head;
    while(copy->next)
    {
        copy = copy->next;
    }
    copy->next = n;
    n->next = NULL;
}
void add_edge(pnode src, node *dest, int w)
{
    pedge *h = &(src->edges);
    pedge e = (pedge)malloc(sizeof(edge));
    if (e==NULL)
    {
        printf("error");
        return;
    }
    e->endpoint = &(*dest);
    e->weight = w;
    e->next = NULL;
    if(!*h)
    {
        *h = e;
        src->edges=*h;
        return;
    }
    pedge copy = *h;
    while(copy->next)
    {
        copy = copy->next;
    }
    copy->next = e;
}
void build_graph_cmd(pnode *head)
{

    int src_id,dest_id,edge_val,num_of_node,i;
    char c;
    scanf("%d ",&num_of_node);
    graph_size = num_of_node;
    for (i=0;i<num_of_node;i++)
    {
        pnode v = (pnode)malloc(sizeof(node));
        if (v==NULL)
        {
            printf("error");
            return;
        }
        v->node_num = i;
        pedge H = NULL;
        v->edges = H;
        add_node(head,v);
    }
    for (i=0; i<num_of_node;i++)    
    {
        scanf(" %c",&c);
        scanf("%d ",&src_id);
        pnode src = get_node(head,src_id);
        while(scanf("%d ",&dest_id))
        {
            node *dest = get_node(head,dest_id);
            scanf("%d ",&edge_val);
            add_edge(src,dest,edge_val);
        }
    }  
    return;
}
void printGraph_cmd(pnode head)
{
    pnode nodes = head;
    printf("next node id -%d\n",head->next->node_num);
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
void insert_node_cmd(pnode *head)
{
    int id,dest_id,edge_val;
    scanf(" %d",&id);
    pnode new_node;
    if (get_node(head,id)!=NULL)
    {
        pnode temp = get_node(head,id);
        free_edge(&(temp->edges));
        if (temp->node_num == (*head)->node_num)
        {
            new_node = temp;
            new_node -> edges = NULL;
            new_node->next = (*head)->next;
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
                pnode new_node = prev->next;
                new_node->edges = NULL;
                prev->next = new_node;
            }
            else
            {
                new_node = prev->next;
                new_node->edges = NULL;
                pnode *t = &(prev->next->next);
                prev->next = new_node;
                new_node->next = *t;
            }

        }
    }
    else
    {
        new_node = (pnode)malloc(sizeof(node));
        new_node->node_num = id;
        new_node->edges=NULL;
        add_node(head,new_node);
        graph_size += 1;
    }
    while (scanf("%d ",&dest_id))
    {
        node *dest = get_node(head,dest_id);
        scanf("%d ",&edge_val);
        add_edge(new_node,dest,edge_val);
    }
    return ;
}
void remove_edge(pedge *head,pedge *to_remove)
{
    if ((*head)->endpoint->node_num==(*to_remove)->endpoint->node_num)
    {
        *head = (*head)->next;
        free(*to_remove);
        return;
    }
    pedge copy = *head;
    pedge prev = *head;
    while(prev->next&&prev->next->endpoint->node_num!=(*to_remove)->endpoint->node_num)
    {
        prev = prev-> next;
        copy = copy -> next;
    }
    if(!prev->next->next){
        copy = copy->next;
        free(copy);
        prev->next = NULL;
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
    int id = -1;
    scanf("%d",&id);
    pnode temp = get_node(head,id);
    free_edge(&(temp->edges));
    //printGraph_cmd(*head);
    while (copy)
    {
        if(copy->node_num != id && copy->edges)
        {
            if(copy->edges->endpoint->node_num != id)
            {
                pedge edge_copy = copy->edges;
                while (edge_copy->next)
                {
                    if (edge_copy->next->endpoint->node_num==id)
                    {
                        pedge remo_ed = edge_copy->next;
                        edge_copy->next = edge_copy->next->next;
                        free(remo_ed);
                        break;
                    }
                    edge_copy = edge_copy->next;
                }
            }
            else
            {
                if(copy->edges->next == NULL)
                {
                    pedge remo_edg = copy->edges;
                    copy->edges = NULL;
                    free(remo_edg);
                }
                else
                {
                    pedge remo_edg = copy->edges;
                    copy->edges = remo_edg->next;
                    free(remo_edg);
                }
            }
                
        }
        
        copy = copy->next;
    
    }
    if (id == (*head)->node_num)
    {
        *head = (*head)->next;
        free(temp);
        return;
    }
    //copy = *head;
    pnode prev = *head;
    while (prev->next->node_num != id)
    {
        prev = prev->next;
    }
    copy = prev->next;
    prev->next = prev->next->next;
    free(copy);
    /*while(prev->next && prev->next->node_num != id)
    {
        prev = prev-> next;
        copy = copy -> next;
    }
    if(!prev->next->next)
    {
        prev->next = NULL;
        copy = copy->next;
        free(temp);
        return;
    }
    copy = copy->next;
    //pnode t = copy;
    prev->next = prev->next->next;
    free(temp);*/
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
        printf("Dijsktra shortest path: %d \n",-1);
    }
    else
        printf("Dijsktra shortest path: %d \n",mat[findid(src,find_id)][findid(dest,find_id)]);
    free(find_id);
    for ( i = 0; i < graph_size; i++)
    {
        free(mat[i]);
    }
    free(mat);
    
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
    int c;
    int i,j,g;
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
        printf("TSP shortest path: %d \n",-1) ;
    }
    else
        printf("TSP shortest path: %d \n",ans);
    for (i =0; i<c+1;i ++)
    {   
        free(dist[i]);
    }
    free(dist);
    for(i=0;i<graph_size;i++)
    {
        free(mat[i]);
    }
    free(mat);
    free(p);
    free(cities);
    free(find_id);
    
}

int main()
{
    pnode head = NULL;
    char c = '\0';
    while (scanf("%c", &c) != EOF && c!='~')
    {
        if(c=='A')
        {
            //printf("start new graph\n");
            if (head!=NULL)
            {
                pnode temp = head;
                while(temp)
                {
                    pedge edge_temp = temp->edges;
                    while (edge_temp)
                    {
                        pedge edge_to_remove = edge_temp;
                        edge_temp = edge_temp->next;
                        free(edge_to_remove);
                    }
                    pnode node_to_remove = temp;
                    temp = temp->next;
                    free(node_to_remove);   
                }
            }
            head = NULL;
            build_graph_cmd(&head);
            //printGraph_cmd(head);
        }
        else if(c=='B')
        {
            //printf("add node\n");
            insert_node_cmd(&head);
        }
        else if(c=='D')
        {
            //printf("delete node\n");
            delete_node_cmd(&head);
        }
        else if(c=='S')
        {
            //printf("short path\n");
            shortsPath_cmd(head);
        }
        else if(c=='T')
        {
            //printGraph_cmd(head);
            //printf("travel problem\n");
            TSP_cmd(head);
        }
    }
    deleteGraph_cmd(&head);
    free(head);
}